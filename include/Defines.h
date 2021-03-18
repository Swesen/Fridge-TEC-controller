#ifndef __DEFINES_H__
#define __DEFINES_H__

// Pin Configuration
#define FANSENS 2   // D2 = FAN RPM input can't be changed, as it is used with interupt0
#define FANPWM 3    // D3 = FAN PWM output can't be changed, as it is used with timer2
#define MOSPIN 9    // D9 = gate of MOSFET can't be changed, as it is used with timer0
#define NEGBTNPIN 5 // D5 = BUTTON -
#define POSBTNPIN 7 // D7 = BUTTON +
#define TEMPPIN A1  // A1 = TEMP SENS

// Declaration for a SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLEDSDA A4    // A4 = DISPLAY SDA can't be changed, the only dedicated SDA pin
#define OLEDSCL A5    // A5 = DISPLAY SCL can't be changed, the only dedicated SCL pin


// Settings Configuration

// OLED
#define SCREEN_WIDTH 128              // OLED display width, in pixels
#define SCREEN_HEIGHT 64              // OLED display height, in pixels
#define OLEDADDRESS 0x3C              // OLED display address
#define BOOTSCREENTEXT "Linus Fridge" // Text to show on bootscreen
#define DISPLAYONTIME 10 * 60000      // Time to show normal display before turning it of (* 60000 to convert minutes to miliseconds)

// Buttons
#define BTNDEBOUNCE 20 // Debounce delay ms
#define BTNHOLDTIME 500 // time before a button is set as hold
#define BTNSPEEDINC 10 // Button incremental speed

// Temperature
#define TEMPRESISTOR 10000          // Temperature resistor value
#define TEMPSMOOTHING 5             // Values to read to smooth the readings
#define TEMPSAMPLERATE 1000         // Time between Temperature readings
#define TEMPTHERMISTORNOMINAL 10000 // resistance at TEMPERATURENOMINAL degrees C
#define TEMPERATURENOMINAL 25       // temperature at nominal resistance (almost always 25 C)
#define BCOEFFICIENT 3950           // The beta coefficient of the thermistor (usually 3000-4000)

// Fan
#define FANSENSTIMEOUT 150000 // Fan timeout in micro seconds

// EEPROM
#define ROMFANPWM 0    // Fan PWM EEPROM address
#define ROMTEMP 8      // Targget temperature EEPROM address
#define EEPROMWRITE 10 // wait this many seconds after last change before saving to eeprom

#endif // __DEFINES_H__