#include <Arduino.h>
#include "Defines.h"
#include "TECController.h"

TECController::TECController(char mosFetPin)
{
    this->mosFetPin = mosFetPin;
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

void TECController::updatePWM(float percent) 
{
    // convert percentage to PWM equivilent
    OCR1A = (unsigned char)(254/percent + 0.5);
}
