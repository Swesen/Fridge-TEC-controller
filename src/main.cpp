#include <Arduino.h>
#include <EEPROM.h>
#include "Defines.h"
#include "Temperature.h"
#include "OLED.h"
#include "Fan.h"

/*-----------
   Variables
  -----------*/
unsigned long lastMillis[4] = {0, 0, 0, 0};
int timerStop = 0, Mode = 0, defrostTimer = 15, buttonRepeat = BTNSPEEDINC * 10, fanSpeed = 0;
float temp = 20, setTemp = 10;
byte PWM = 0;
bool writeROM = false, dimOLED = false;

void setup()
{
  // set pin modes
  pinMode(FANSENS, INPUT_PULLUP);
  pinMode(NEGBTNPIN, INPUT_PULLUP);
  pinMode(POSBTNPIN, INPUT_PULLUP);
  pinMode(MOSPIN, OUTPUT);
  pinMode(TEMPPIN, INPUT);

  // read saved values from EEPROM
  EEPROM.get(ROMPWM, PWM);
  EEPROM.get(ROMTEMP, setTemp);

  // if EEPROM values are out of range reset to default
  if (setTemp > 30 || setTemp < 0)
  {
    setTemp = 30;
    EEPROM.put(ROMTEMP, setTemp);
  }
  // if EEPROM values are out of range reset to default
  if (PWM > 100 || PWM < 0)
  {
    PWM = 30;
    EEPROM.put(ROMPWM, PWM);
  }

  // perform necessairy setups
  fanSetup();
  mosPWMSetup();
  startOLED();
  updateOLED();
}

int readButtons()
{
  // Read if one or both buttons are pressed
  bool posBtn = !digitalRead(POSBTNPIN);
  bool negBtn = !digitalRead(NEGBTNPIN);
  if (posBtn && negBtn) // both buttons
  {
    return 3;
  }
  else if (posBtn) // Possitive button
  {
    return 2;
  }
  else if (negBtn) // Negative button
  {
    return 1;
  }
  else // no button
    return 0;
}

void loop()
{

  // check current time to use with every timer
  unsigned long currentMillis = millis();

  // if millis() rolls over reset update timer
  if (currentMillis < lastMillis[0])
    lastMillis[0] = currentMillis;

  // if not in defrost mode update update
  if (Mode != 3)
  {
    mosPWMUpdate();
  }
  else
  {
    OCR1A = 0;
  }

  // update info if TEMPSAMPLERATE time has passed
  if ((currentMillis - lastMillis[0]) > TEMPSAMPLERATE)
  {
    lastMillis[0] = currentMillis;

    getTemp();
    setFanSpeed();
    getFanRPM();

    // exit defrost mode when timer goes to zero
    if (timerStop - int((currentMillis - lastMillis[4]) / 60000) <= 0 && Mode == 3)
    {
      Mode = 0;
      lastMillis[2] = currentMillis;
    }

    // update display
    if (Mode != 0) // display always on when not in Mode 0
    {
      defrostTimer = timerStop - int((currentMillis - lastMillis[4]) / 60000);
      dimOLED = false;
      updateOLED();
    }
    else if ((currentMillis - lastMillis[2]) > 60000 && (currentMillis - lastMillis[2]) < DISPLAYTIME) // dim display 1min after last input until DISPLAYTIME
    {
      dimOLED = true;
      updateOLED();
    }
    else if ((currentMillis - lastMillis[2]) < 60000) // display enabled as long as there was input within DISPLAYTIME
    {
      dimOLED = false;
      updateOLED();
    }
    else // turn off display
    {
      Mode = -1;
      dimOLED = true;
      updateOLED();
    }
  }

  // wait 10 seconds after last button release to write to EEPROM
  if (writeROM == true)
  {
    if ((currentMillis - lastMillis[2]) > EEPROMWRITE * 1000)
    {
      EEPROM.put(ROMPWM, PWM);
      EEPROM.put(ROMTEMP, setTemp);
      writeROM = false;
    }
  }

  // Read button states
  int buttonState = readButtons();

  // ignore if no button is pressed
  if (buttonState != 0)
  {

    // enable display if display is off and reset timer
    if (Mode == -1)
    {
      Mode = 0;
      lastMillis[2] = currentMillis;
    }

    // check if button is pressed for longer than BTNDEBOUNCE value
    if ((currentMillis - lastMillis[1]) > BTNDEBOUNCE)
    {
      // perform action based on what button is pressed
      switch (buttonState)
      {
      case 3: // Both buttons pressed = change mode
        while (readButtons() != 0)
          ;
        Mode++;
        timerStop = 15;
        lastMillis[4] = currentMillis;
        if (Mode >= 4)
        {
          Mode = 0;

          lastMillis[2] = currentMillis;
        }

        dimOLED = false;
        updateOLED();
        break;

      case 2: // Possitive button pressed = increase a value based on mode
        while (readButtons() == 2)
        {
          if (Mode == 1)
          {
            setTemp += 0.1;
          }
          else if (Mode == 2 && PWM <= 99)
          {
            PWM++;
          }
          else if (Mode == 3)
          {
            timerStop++;
            lastMillis[4] = currentMillis;
          }

          dimOLED = false;
          updateOLED();

          if (buttonRepeat > BTNSPEEDINC)
          {
            buttonRepeat -= BTNSPEEDINC;
          }

          delay(buttonRepeat);
        }

        // zero out timer and write to EEPROM after EEPROMWRITE seconds
        lastMillis[2] = currentMillis;
        writeROM = true;
        break;

      case 1: // Negative button pressed = decrease a value based on mode
        while (readButtons() == 1)
        {
          if (Mode == 1)
          {
            setTemp -= 0.1;
          }
          else if (Mode == 2 && PWM >= 1)
          {
            PWM--;
          }
          else if (Mode == 3 && timerStop >= 1)
          {
            timerStop--;
            lastMillis[4] = currentMillis;
          }

          dimOLED = false;
          updateOLED();
          if (buttonRepeat > BTNSPEEDINC)
          {
            buttonRepeat -= BTNSPEEDINC;
          }

          delay(buttonRepeat);
        }
        // zero out timer and write to EEPROM after EEPROMWRITE seconds
        lastMillis[2] = currentMillis;
        writeROM = true;
        break;

      default:
        // do nothing
        break;
      }
    }
  }
  else
  {
    // if no button is pressed reset timer
    lastMillis[1] = currentMillis;
    buttonRepeat = BTNSPEEDINC * 10;
  }
}
