#include "Defines.h"
#include "Logo.h"
#include <SPI.h>
#include <Wire.h>
#include <splash.h>
#include <Adafruit_SSD1306.h>
#include "Temperature.h"

void startOLED();
void updateOLED();
void OLEDoff();