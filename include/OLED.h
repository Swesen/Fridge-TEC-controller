#ifndef __OLED_H__
#define __OLED_H__

#include <String.h>

class OLED
{
private:
    int dropCycle;

    void printCurrentTemp(char currentTemperature, char textSize);
    void printSetTemp(char setTemperature, bool selected);
    void printFanInfo(int fanSpeed, byte fanPWM, bool selected);
    void printMosStatus();
    void printDefrostInfo(int defrostTimer);

public:
    byte mode;

    OLED(String bootText);

    void update(byte mode, bool dimOLED, char currentTemperature, char setTemperature, int fanSpeed, byte fanPWM, int defrostTimer);
};

#endif // __TEC_OLED_H__