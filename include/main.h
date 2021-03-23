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
    AmountOfTimers
};

void loadEEPROMValues();

void saveEEPROMValues();

int8_t readButtons();

void changeSettings(int8_t changeCurrentSetting);

void setScreenLightMode();

void update();

void resetTimers();

#endif // __MAIN_H__