#include "Fan.h"

// external variables
extern byte PWM;
extern int fanSpeed;

void fanSetup()
{   
    // The timer configuration was complex so I found this code snippet on some forum
    // generate 25kHz PWM pulse rate on Pin 3
    pinMode(FANPWM, OUTPUT);                               // OCR2B sets duty cycle
    TCCR2A = 0;                                            // TC2 Control Register A
    TCCR2B = 0;                                            // TC2 Control Register B
    TIMSK2 = 0;                                            // TC2 Interrupt Mask Register
    TIFR2 = 0;                                             // TC2 Interrupt Flag Register
    TCCR2A |= (1 << COM2B1) | (1 << WGM21) | (1 << WGM20); // OC2B cleared/set on match when up/down counting, fast PWM
    TCCR2B |= (1 << WGM22) | (1 << CS21);                  // prescaler 8
    OCR2A = 79;                                            // TOP overflow value (Hz)
    OCR2B = 10;
    pinMode(FANSENS, INPUT_PULLUP); // Starts reading
}

void setFanSpeed()
{
    // convert user set fan percentage to PWM timer number
    int val = round((PWM / 100.0) * 79);
    OCR2B = val;
}

void getFanRPM()
{
    // use the time between fan pulses to get RPM
    unsigned long time = pulseIn(FANSENS, HIGH, FANSENSTIMEOUT);
    fanSpeed = (1000000 * 60) / (time * 4);
}