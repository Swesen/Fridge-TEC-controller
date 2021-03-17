#include <Arduino.h>
#include <EEPROM.h>
#include "Defines.h"

/*-----------
   Variables
  -----------*/
unsigned long lastMillis = 0;
int timerStop = 0, Mode = 0, defrostTimer = 15, buttonRepeat = BTNSPEEDINC * 10, fanSpeed = 0;
float temp = 20, setTemp = 10;
unsigned char PWM = 0;
bool writeROM = false, dimOLED = false;

void setup()
{
  // set pin modes
  pinMode(FANSENS, INPUT_PULLUP);

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
}

void loop()
{

  // check current time to use with every timer
  unsigned long currentMillis = millis();

  // if millis() rolls over reset update timer
  if (currentMillis < lastMillis)
    lastMillis = currentMillis;
}
