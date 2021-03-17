#ifndef __DEFINES_H__
#define __DEFINES_H__

/*--------------------
   Pin Configuration
  --------------------
*/
#define FANSENS 2                 // D2 = FAN RPM output
#define FANPWM 3                  // D3 = FAN PWM input
#define NEGBTNPIN 5               // D5 = BUTTON -
#define POSBTNPIN 7               // D7 = BUTTON +
#define MOSPIN 9                  // D9 = gate of MOSFET

#define TEMPPIN A1                // A1 = TEMP SENS

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1             // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLEDSDA A4                // A4 = DISPLAY SDA
#define OLEDSCL A5                // A5 = DISPLAY SCL

/*
  ---------------
  Settings Configuration
  ---------------
*/
#define SCREEN_WIDTH 128          // OLED display width, in pixels
#define SCREEN_HEIGHT 64          // OLED display height, in pixels
#define OLEDADDRESS 0x3C          // OLED display address

#define BOOTSCREENTEXT "Linus Fridge"



#define DISPLAYTIME 10 * 60000     // Time to show normal display before turning it of (* 60000 to convert minutes to miliseconds)

#define BTNDEBOUNCE 20            // Debounce delay ms
#define BTNSPEEDINC 10            // Button incremental speed
#define TEMPRESISTOR 10000        // Temperature resistor value
#define NUMSAMPLES 5              // Values to read to smooth the readings
#define TEMPSAMPLERATE 1000       // Time between Temperature readings
#define THERMISTORNOMINAL 10000   // resistance at 25 degrees C
#define TEMPERATURENOMINAL 25     // temp. for nominal resistance (almost always 25 C)
#define BCOEFFICIENT 3950         // The beta coefficient of the thermistor (usually 3000-4000)
#define OFFSETTEMP 0             // Offset temperature

#define FANSENSTIMEOUT 150000     // Fan timeout in micro seconds

#define ROMPWM 0                  // PWM EEPROM address
#define ROMTEMP 8 // setTemp EEPROM address
#define EEPROMWRITE 10

#endif // __DEFINES_H__