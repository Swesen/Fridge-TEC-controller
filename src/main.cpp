#include <Arduino.h>
#include <EEPROM.h>
#include "main.h"
#include "Fan.h"
#include "OLED.h"
#include "Defines.h"
#include "Buttons.h"
#include "Temperature.h"
#include "TECController.h"

// Variables
unsigned long lastMillis = 0;
int Mode = 0, defrostTimer = 15;
float targetTemperature = 10;
byte fanPWM = 0;
bool writeROM = false, dimOLED = false;

// Objects
OLED screen(BOOTSCREENTEXT);
Buttons buttons(NEGBTNPIN, POSBTNPIN, BTNDEBOUNCE);
Fan fan(FANSENS, FANPWM, FANSENSTIMEOUT);
Temperature thermistor(TEMPPIN, TEMPSMOOTHING, TEMPRESISTOR, TEMPTHERMISTORNOMINAL, TEMPERATURENOMINAL, BCOEFFICIENT);
TECController peltier(MOSPIN);

void setup()
{
  loadEEPROMValues();
}

void loop()
{

  // check current time to use with every timer
  unsigned long currentMillis = millis();

  // if millis() rolls over reset update timer
  if (currentMillis < lastMillis)
    lastMillis = currentMillis;
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