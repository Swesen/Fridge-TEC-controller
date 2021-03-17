#ifndef __OLED_H__
#define __OLED_H__

#include <Arduino.h>

class OLED
{
private:
    int dropCycle;

    void printCurrentTemp(char currentTemperature, char textSize);
    void printSetTemp(char setTemperature, bool selected);
    void printFanInfo(int fanSpeed, unsigned char fanPWM, bool selected);
    void printMosStatus();
    void printDefrostInfo(int defrostTimer);

public:
    unsigned char mode;

    OLED(String bootText);

    void update(unsigned char mode, bool dimOLED, char currentTemperature, char setTemperature, int fanSpeed, unsigned char fanPWM, int defrostTimer);
};

#endif // __TEC_OLED_H__