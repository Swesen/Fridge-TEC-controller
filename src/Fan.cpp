#include <Arduino.h>
#include "Fan.h"

Fan::Fan(char fanSensPin, char fanPWMPin, unsigned long fanSensTimeOut)
{
    this->fanSensPin = fanSensPin;
    this->fanPWMPin = fanPWMPin;
    this->fanSensTimeOut = fanSensTimeOut;

    pinMode(fanPWMPin, OUTPUT);
    pinMode(fanSensPin, INPUT_PULLUP);
    setupTimer2();
}

int Fan::getFanRPM()
{
    // convert the time between signal pulses to RPM
    return 1000000 * 60 / pulseIn(fanSensPin, HIGH, fanSensTimeOut) * 4;
}

void Fan::setFanSpeed(float percent) 
{
    // convert percentage to PWM timer equivilent
    OCR2B = (unsigned char)(79 / percent + 0.5);
}

void Fan::setupTimer2()
{
    // clear timer 2
    TCCR2A = 0;
    TCCR2B = 0;
    TIMSK2 = 0;
    TIFR2 = 0;
    // set timer 2 to fast PWM, non-inverted mode
    TCCR2A |= (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
    // set reversed fast PWM mode, prescaler clock 16M / 8 = 2M
    TCCR2B |= (1 << WGM22) | (1 << CS21);
    // 2M / 80 = 25kHz
    OCR2A = 79;
    // OCR2A / OCR2B = PWM%
    OCR2B = 10;
}
