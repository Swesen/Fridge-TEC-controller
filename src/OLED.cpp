#include <SPI.h>
#include <Wire.h>
#include <splash.h>
#include <Adafruit_SSD1306.h>
#include "Defines.h"
#include "Logo.h"
#include "Temperature.h"
#include "OLED.h"

int dropCycle = 0;

// external variables
extern float temp, setTemp;
extern byte PWM;
extern int Mode, defrostTimer, fanSpeed;
extern bool dimOLED;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void startOLED()
{
    String bootText = BOOTSCREENTEXT;
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

// Information mode
void drawPage1()
{
    display.setTextColor(1);
    display.setTextSize(3);
    display.print(temp, 1);
    display.print((char)247);
    display.println("C");

    display.setTextSize(2);
    display.print("Set:");
    display.print(setTemp, 1);
    display.print((char)247);
    display.println("C");

    display.setTextSize(1);
    display.print("Fan:");
    display.print(fanSpeed);
    display.print("RPM  ");
    display.print(PWM);
    display.println("%");

    display.print("Mos:");
    display.print(OCR1A);
}

// set target temp mode
void drawPage2()
{
    display.setTextColor(1);
    display.setTextSize(1);
    display.print(temp, 1);
    display.print((char)247);
    display.println("C");

    display.setTextColor(0, 1);
    display.setTextSize(2);
    display.print("Set:");
    display.print(setTemp, 1);
    display.print((char)247);
    display.println("C");

    display.setTextColor(1);
    display.setTextSize(1);
    display.print("Fan:");
    display.print(fanSpeed);
    display.print("RPM  ");
    display.print(PWM);
    display.println("%");

    display.print("Mos:");
    display.print(OCR1A);
}

// set fan speed mode
void drawPage3()
{
    display.setTextColor(1);
    display.setTextSize(1);
    display.print(temp, 1);
    display.print((char)247);
    display.println("C");

    display.setTextColor(1);
    display.setTextSize(1);
    display.print("Set:");
    display.print(setTemp, 1);
    display.print((char)247);
    display.print("C ");
    display.print("Fan:");
    display.print(fanSpeed);
    display.println("RPM");

    display.setTextColor(0, 1);
    display.setTextSize(2);
    display.print("Fan:");
    display.print(PWM);
    display.println("%");

    display.setTextColor(1);
    display.setTextSize(1);
    display.print("Mos:");
    display.print(OCR1A);

}

// Defrost mode
void drawPage4()
{
    display.setTextColor(1);
    display.setTextSize(2);
    display.print(temp, 1);
    display.print((char)247);
    display.println("C");

    display.setTextSize(1);
    display.print("Set:");
    display.print(setTemp, 1);
    display.print((char)247);
    display.println("C");

    display.setTextSize(1);
    display.print("Fan:");
    display.print(fanSpeed);
    display.print("RPM ");
    display.print(PWM);
    display.println("%");


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

void updateOLED()
{
    // get ready to update oled with new info
    display.dim(dimOLED);
    display.clearDisplay();
    display.setCursor(0, 0);

    // check which mode to show on the oled
    switch (Mode)
    {
    case -1:    // turn off display
        break;
    case 0:     // Information mode
        drawPage1();
        break;
    case 1:     // set target temp mode
        drawPage2();
        break;
    case 2:     // set fan speed mode
        drawPage3();
        break;
    case 3:     // defrost mode
        drawPage4();
        break;
    default:
        break;
    }

    // display button info on screen for modes with settings
    if (Mode > 0)
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