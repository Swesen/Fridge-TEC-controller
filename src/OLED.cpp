#include <SPI.h>
#include <Wire.h>
#include <splash.h>
#include <Adafruit_SSD1306.h>
#include "OLED.h"
#include "Defines.h"
#include "Logo.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

OLED::OLED(String bootText)
{
    display.begin(SSD1306_SWITCHCAPVCC, OLEDADDRESS);

    display.clearDisplay();
    display.display();

    display.drawBitmap(SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2 - 28, snowflake, 40, 40, 1);
    display.setTextColor(1);
    display.setTextSize(1);
    display.setCursor(SCREEN_WIDTH / 2 - (bootText.length() * 6) / 2, 44);
    display.print(bootText);
    display.display();
    delay(5000);
    display.clearDisplay();
}

void OLED::update(unsigned char mode, bool dimOLED, char currentTemperature, char setTemperature, int fanSpeed, unsigned char fanPWM, int defrostTimer)
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
    case 0: // turn off display
        break;
    case 1: // Information mode
        tempSize = 3;
        break;
    case 2: // set target temperature mode
        tempSelected = true;
        break;
    case 3: // set fan speed mode
        fanSelected = true;
        break;
    case 4: // defrost mode
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

void OLED::printFanInfo(int fanSpeed, unsigned char fanPWM, bool selected)
{
    display.setTextColor(1);
    display.setTextSize(1);
    display.print("Fan:");
    display.print(fanSpeed);

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
}

void OLED::printDefrostInfo(int defrostTimer)
{
    display.print("Defrost:");
    display.print(defrostTimer);
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