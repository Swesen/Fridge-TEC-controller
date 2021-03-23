#ifndef __OLED_H__
#define __OLED_H__

#include <SPI.h>
#include <Wire.h>
#include <splash.h>
#include <Adafruit_SSD1306.h>
#include <String.h>
#include "main.h"

class OLED
{
private:
    byte dropCycle = 0;

    Adafruit_SSD1306 display;

    void printCurrentTemp(char currentTemperature, char textSize);
    void printSetTemp(char setTemperature, bool selected);
    void printFanInfo(int *fanSpeed, byte fanPWM, bool selected);
    void printMosStatus();
    void printDefrostInfo(byte defrostTimer);

public:
    OLED(uint8_t w, uint8_t h, TwoWire *twi, int8_t rst_pin);

    void start(String bootText);
    void update(Mode mode, bool dimOLED, char currentTemperature, char setTemperature, int *fanSpeed, byte fanPWM, byte defrostTimer);
    void print(String text);
    void clear();
};

#endif // __TEC_OLED_H__