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

    

    void printCurrentTemp(double currentTemperature, byte textSize);
    void printSetTemp(double setTemperature, bool selected);
    void printFanInfo(int *fanSpeed, byte fanPWM, bool selected);
    void printMosStatus(byte peltierPWM);
    void printDefrostInfo(byte defrostTimer);

public:
Adafruit_SSD1306 display;
    OLED(uint8_t w, uint8_t h, TwoWire *twi, int8_t rst_pin);

    void start(String bootText);
    void update(Mode mode, bool dimOLED, double currentTemperature, double setTemperature, int *fanSpeed, byte fanPWM, byte peltierPWM, byte defrostTimer);
    void print(String text);
    void clear();
};

#endif // __TEC_OLED_H__