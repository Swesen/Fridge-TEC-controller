#ifndef __OLED_H__
#define __OLED_H__

#include <String.h>
#include "main.h"

class OLED
{
private:
    int dropCycle = 0;

    void printCurrentTemp(char currentTemperature, char textSize);
    void printSetTemp(char setTemperature, bool selected);
    void printFanInfo(int fanSpeed, byte fanPWM, bool selected);
    void printMosStatus();
    void printDefrostInfo(int defrostTimer);

public:

    OLED(String bootText);

    void update(Mode mode, bool dimOLED, char currentTemperature, char setTemperature, int fanSpeed, byte fanPWM, int defrostTimer);
};

#endif // __TEC_OLED_H__