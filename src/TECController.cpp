#include <Arduino.h>
#include "Defines.h"
#include "TECController.h"

TECController::TECController(char mosFetPin)
{
    this->mosFetPin = mosFetPin;

}

void TECController::start() 
{
        pinMode(MOSPIN, OUTPUT);

    // reset timer settings
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;

    // mode 5: fast PWM, 8bit. no prescaling = 63kHz
    TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
    TCCR1B |= (1 << WGM12) | (1 << CS10);

    OCR1A = 254;
}


void TECController::setPWM(float percentage)
{
    // convert percentage to PWM equivilent
    OCR1A = (byte)(254 / percentage + 0.5);
}