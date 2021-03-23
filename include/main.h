#ifndef __MAIN_H__
#define __MAIN_H__

enum Mode
{
    ScreenOff,
    Information,
    SetTagetTemp,
    SetFanSpeed,
    Defrost,
    First = ScreenOff,
    Last = Defrost
};
enum Timer
{
    UpdateTimer,
    ButtonStateTimer,
    SettingChangeTimer,
    DefrostTimer,
    EEPROMTimer,
    AmountOfTimers
};

void loadEEPROMValues();

void saveEEPROMValues(unsigned long currentMillis);

int8_t readButtons(unsigned long currentMillis);

void changeSettings(int8_t changeCurrentSetting, unsigned long currentMillis);

void setScreenLightMode(unsigned long currentMillis);

void update(unsigned long currentMillis);

void resetTimers(unsigned long currentMillis);

#endif // __MAIN_H__