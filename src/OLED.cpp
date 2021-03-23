
#include "OLED.h"
#include "Defines.h"
#include "Logo.h"

OLED::OLED(uint8_t w, uint8_t h, TwoWire *twi, int8_t rst_pin) : display(w, h, twi, rst_pin) {}

void OLED::start(String bootText)
{

    display.begin(SSD1306_SWITCHCAPVCC, OLEDADDRESS);

    display.clearDisplay();
    display.display();
    delay(500);
    display.drawBitmap(SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2 - 28, snowflake, 40, 40, 1);
    display.setTextColor(1);
    display.setTextSize(1);
    display.setCursor(SCREEN_WIDTH / 2 - (bootText.length() * 6) / 2, 44);
    display.print(bootText);
    display.display();
    delay(2000);
    display.clearDisplay();
}

void OLED::update(Mode mode, bool dimOLED, char currentTemperature, char setTemperature, int *fanSpeed, byte fanPWM, byte defrostTimer)
{
    int tempSize = 1;
    bool tempSelected = false;
    bool fanSelected = false;
    bool defrosting = false;

    // get ready to update oled with new info
    display.dim(dimOLED);
    display.clearDisplay();
    display.setCursor(0, 0);

    // check which mode to show on the oled
    switch (mode)
    {
    case Information:
        tempSize = 3;
        break;

    case SetTagetTemp:
        tempSelected = true;
        break;

    case SetFanSpeed:
        fanSelected = true;
        break;

    case Defrost:
        tempSize = 2;
        defrosting = true;
        break;

    default:
        break;
    }

    printCurrentTemp(currentTemperature, tempSize);

    printSetTemp(setTemperature, tempSelected);

    printFanInfo(fanSpeed, fanPWM, fanSelected);

    if (defrosting)
    {
        printDefrostInfo(defrostTimer);
    }
    else
    {
        printMosStatus();
    }

    // display button info on screen for modes with settings
    if (mode > 0)
    {
        display.setCursor(0, SCREEN_HEIGHT - 7 * 2);
        display.setTextColor(0, 1);
        display.setTextSize(2);
        display.print(" - ");
        display.setCursor(SCREEN_WIDTH - 18 * 2, SCREEN_HEIGHT - 7 * 2);
        display.print(" + ");
    }

    display.display();
}

void OLED::print(String text)
{
    display.setTextColor(1);
    display.setTextSize(1);
    display.println(text);
    display.display();
}

void OLED::clear()
{
    display.clearDisplay();
    display.setCursor(0, 0);
}

void OLED::printCurrentTemp(char currentTemperature, char textSize)
{
    display.setTextColor(1);
    display.setTextSize(textSize);
    display.print(currentTemperature, 1);
    display.print((char)247);
    display.println("C");
}

void OLED::printSetTemp(char setTemperature, bool selected)
{
    if (selected)
    {
        display.setTextColor(0, 1);
    }

    display.setTextSize(2);
    display.print("Set:");
    display.print(setTemperature, 1);
    display.print((char)247);
    display.println("C");
}

void OLED::printFanInfo(int *fanSpeed, byte fanPWM, bool selected)
{
    display.setTextColor(1);
    display.setTextSize(1);
    display.print("Fan:");
    display.print(int(*fanSpeed));

    if (selected)
    {
        display.setTextColor(0, 1);
        display.setTextSize(2);
    }
    display.print("RPM  ");
    display.print(fanPWM);
    display.println("%");
}

void OLED::printMosStatus()
{
    display.setTextColor(1);
    display.setTextSize(1);
    display.print("Mos:");
    display.print(OCR1A);
    display.println("%");
}

void OLED::printDefrostInfo(byte defrostTimer)
{
    display.print("Defrost:");
    display.print(int(defrostTimer));
    display.print("min");

    // animate melting snowflake
    display.drawBitmap(128 - 40, 0, snowflake, 40, 40, 1);
    switch (dropCycle)
    {
    case 0:
        display.drawBitmap(128 - 35, 34, drop, 12, 12, 1);
        dropCycle++;
        break;
    case 1:
        display.drawBitmap(128 - 35, 37, drop, 12, 12, 1);
        dropCycle++;
        break;
    case 2:
        display.drawBitmap(128 - 17, 34, drop, 12, 12, 1);
        dropCycle++;
        break;
    case 3:
        display.drawBitmap(128 - 17, 37, drop, 12, 12, 1);
        dropCycle = 0;
        break;
    default:
        break;
    }
}