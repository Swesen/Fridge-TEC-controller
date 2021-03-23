#ifndef __DEFINES_H__
#define __DEFINES_H__

#define MINUTETOMS(x) x * 60000 // convert minutes to milliseconds
#define SECONDTOMS(x) x * 1000  // convert seconds to milliseconds

// Pin Configuration
#define FANSENS 2   // D2 = FAN RPM input can't be changed, as it is used with interupt0
#define FANPWM 3    // D3 = FAN PWM output can't be changed, as it is used with timer2
#define MOSPIN 9    // D9 = gate of MOSFET can't be changed, as it is used with timer0
#define NEGBTNPIN 5 // D5 = BUTTON -
#define POSBTNPIN 7 // D7 = BUTTON +
#define TEMPPIN A1  // A1 = TEMP SENS

// OLED Pins
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLEDSDA A4    // A4 = DISPLAY SDA can't be changed, the only dedicated SDA pin
#define OLEDSCL A5    // A5 = DISPLAY SCL can't be changed, the only dedicated SCL pin

// Settings Configuration
#define UPDATEINTERVAL 1000 // ms between updates of OLED, temperature, fan speed etc.
#define DEFROSTTIMERDEFAULT 15
// OLED
#define SCREEN_WIDTH 128              // OLED display width, in pixels
#define SCREEN_HEIGHT 64              // OLED display height, in pixels
#define OLEDADDRESS 0x3C              // OLED display address
#define BOOTSCREENTEXT "Linus Fridge" // Text to show on bootscreen
#define OLEDONTIME MINUTETOMS(10)     // ms before turning off the OLED
#define OLEDDIMTIME MINUTETOMS(2)     // ms before the OLED is dimmed
// Buttons
#define BTNDEBOUNCE 20        // Debounce delay ms
#define BTNHOLDTIME 500       // time before a button is set as hold
#define BTNHOLDSTARTSPEED 500 // the start delay between changes when a button is held
#define BTNHOLDENDSPEED 100   // the smallest delay between changes when a button is held
#define BTNSPEEDINC 10        // the amount to decrease the delay between changes when a button is held
// Temperature
#define TEMPRESISTOR 10000          // Temperature resistor value
#define TEMPSMOOTHING 5             // Values to read to smooth the readings
#define TEMPTHERMISTORNOMINAL 10000 // resistance at TEMPERATURENOMINAL degrees C
#define TEMPERATURENOMINAL 25       // temperature at nominal resistance (almost always 25 C)
#define BCOEFFICIENT 3950           // The beta coefficient of the thermistor (usually 3000-4000)
// PID
#define KP .01
#define KI .001
#define KD 0
// Fan
#define FANSENSTIMEOUT 150000 // Fan timeout in micro seconds
// EEPROM
#define ROMFANPWM 0    // Fan PWM EEPROM address
#define ROMTEMP 8      // Targget temperature EEPROM address
#define EEPROMWRITE SECONDTOMS(10) // wait this many seconds after last change before saving to eeprom

#endif // __DEFINES_H__