#include <Arduino.h>
#include <EEPROM.h>
#include <AutoPID.h>
#include "main.h"
#include "Fan.h"
#include "OLED.h"
#include "Defines.h"
#include "Buttons.h"
#include "Temperature.h"
#include "TECController.h"

// Variables
Mode mode = Information;
unsigned long currentMillis = 0;
unsigned long lastMillis[AmountOfTimers] = {0};
byte defrostTimer = DEFROSTTIMERDEFAULT;
float targetTemperature = 10, currentTemperature = 30, peltierPWM = 100;
byte fanPWM = 0;
bool writeROM = false, dimOLED = false;

byte lastButtonState = 0;
unsigned int delayTillNextChange = BTNHOLDSTARTSPEED;

OLED screen(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Buttons buttons(BTNDEBOUNCE);
Fan fan(FANSENS, FANPWM, FANSENSTIMEOUT);
Temperature thermistor(TEMPPIN, TEMPSMOOTHING, TEMPRESISTOR, TEMPTHERMISTORNOMINAL, TEMPERATURENOMINAL, BCOEFFICIENT);
TECController peltier(MOSPIN);
AutoPID pidController(&currentTemperature, &targetTemperature, &peltierPWM, 0, 100, KP, KI, KD);

void setup()
{
  loadEEPROMValues();

  screen.start(BOOTSCREENTEXT);
  buttons.setupButtons(NEGBTNPIN, POSBTNPIN);
  fan.start();
  thermistor.start();
  peltier.start();
  pidController.setBangBang(4);

  fan.setFanSpeed(fanPWM);
}

void loop()
{
  // get current time to use with every timer
  currentMillis = millis();

  resetTimers();
  int8_t changeCurrentSetting = readButtons();

  changeSettings(changeCurrentSetting);

  update();

  setScreenLightMode();

  saveEEPROMValues();
}

// checks if the timers need to be reset because millis() has rolled over
void resetTimers()
{
  for (byte i = 0; i < AmountOfTimers; i++)
  {
    if (currentMillis < lastMillis[i])
    {
      lastMillis[i] = currentMillis;
    }
  }
}

void loadEEPROMValues()
{
  // read saved values from EEPROM
  EEPROM.get(ROMFANPWM, fanPWM);
  EEPROM.get(ROMTEMP, targetTemperature);

  // if EEPROM values are out of range reset to default
  if (targetTemperature > 30 || targetTemperature < 0)
  {
    targetTemperature = 30;
    EEPROM.put(ROMTEMP, targetTemperature);
  }
  // if EEPROM values are out of range reset to default
  if (fanPWM > 100 || fanPWM < 0)
  {
    fanPWM = 30;
    EEPROM.put(ROMFANPWM, fanPWM);
  }
}

void saveEEPROMValues()
{
  // check if it is time to save new values to EEPROM
  if (lastMillis[SettingChangeTimer] != 0 && currentMillis - lastMillis[SettingChangeTimer] > EEPROMWRITE)
  {
    EEPROM.put(ROMTEMP, targetTemperature);
    EEPROM.put(ROMFANPWM, fanPWM);
    lastMillis[SettingChangeTimer] = 0;
    if (mode != Defrost)
    {
      mode = Information;
    }
  }
}

// handles the button presses
int8_t readButtons()
{
  int8_t changeCurrentSetting = 0;
  byte currentButtonState = buttons.getStatus(currentMillis);

  // in case a new button is pressed
  if (lastButtonState < currentButtonState)
  {
    // start screen if off
    dimOLED = false;
    if (mode == ScreenOff)
    {
      mode = Information;
    }

    lastMillis[ButtonStateTimer] = currentMillis;
    lastButtonState = currentButtonState;
  } // a button was released
  else if (lastButtonState > currentButtonState)
  {
    // increment, decrement or change mode
    switch (lastButtonState)
    {
    case both:
      if (mode == Mode::Last)
      {
        mode = Mode::First;
      }
      else
      {
        mode = Mode(int(mode) + 1);
      }

      if (mode == Defrost)
      {
        defrostTimer = DEFROSTTIMERDEFAULT;
      }
      break;

    case positive:
      changeCurrentSetting = 1;
      break;

    case negative:
      changeCurrentSetting = -1;
      break;

    default:
      break;
    }

    lastMillis[ButtonStateTimer] = currentMillis;
    delayTillNextChange = BTNHOLDSTARTSPEED;
    lastButtonState = currentButtonState;
  } // when one or more buttons are held
  else if (lastButtonState > 0 && currentMillis - lastMillis[ButtonStateTimer] > BTNHOLDTIME && currentMillis - lastMillis[SettingChangeTimer] > delayTillNextChange)
  {
    switch (lastButtonState)
    {
    case positive:
      changeCurrentSetting = 1;
      break;

    case negative:
      changeCurrentSetting = -1;
      break;

    default:
      break;
      if (delayTillNextChange > BTNHOLDENDSPEED)
      {
        delayTillNextChange -= BTNSPEEDINC;
      }
    }
  }

  return changeCurrentSetting;
}

// changes settings based on what the current mode is
void changeSettings(int8_t changeCurrentSetting)
{
  if (changeCurrentSetting != 0 && mode > 1)
  {
    switch (mode)
    {
    case SetTagetTemp:
      targetTemperature += 0.1 * changeCurrentSetting;
      break;

    case SetFanSpeed:
      fanPWM += changeCurrentSetting;
      fan.setFanSpeed(fanPWM);
      break;

    case Defrost:
      defrostTimer += changeCurrentSetting;
      break;

    default:
      break;
    }

    lastMillis[SettingChangeTimer] = currentMillis;
  }
}

// handles the dimming and turning off the screen
void setScreenLightMode()
{
  // check if it is time to turn of the screen
  if (mode != ScreenOff && mode != Defrost)
  {
    if (currentMillis - lastMillis[ButtonStateTimer] > OLEDONTIME)
    {
      mode = ScreenOff;
    }

    if (currentMillis - lastMillis[ButtonStateTimer] > OLEDDIMTIME)
    {
      dimOLED = true;
    }
  }
}

// handles the updating of the readings and screen
void update()
{
  // check if it is time to update
  if (currentMillis - lastMillis[UpdateTimer] > UPDATEINTERVAL)
  {
    currentTemperature = thermistor.getTemperature();
    int fanRPM = fan.getFanRPM();
    screen.update(mode, dimOLED, currentTemperature, targetTemperature, &fanRPM, fanPWM, defrostTimer);
    if (mode == Defrost)
    {
      peltier.setPWM(0);
      if (currentMillis - lastMillis[DefrostTimer] > 60000)
      {
        defrostTimer--;
        lastMillis[DefrostTimer] = currentMillis;
      }
    }
    else
    {
      pidController.run();
      peltier.setPWM(peltierPWM);
    }

    lastMillis[UpdateTimer] = currentMillis;
  }
}