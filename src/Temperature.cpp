#include "Temperature.h"

// internal variables
int tempCurrentVal = 0;
int samples[NUMSAMPLES] = {512, 512, 512, 512, 512};

// external variables
extern float temp, setTemp;

//PID parameters
double Setpoint, Input, Output;
double Kp = 1.5, Ki = 5, Kd = 1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void getTemp()
{
    // tage a new reading and add to samples
    samples[tempCurrentVal] = analogRead(TEMPPIN);
    if (tempCurrentVal >= 4)
    {
        tempCurrentVal = 0;
    }
    else
    {
        tempCurrentVal++;
    }

    // average all the samples out
    float average = 0;
    for (int i = 0; i < NUMSAMPLES; i++)
    {
        average += samples[i];
    }
    average /= NUMSAMPLES;

    // convert the value to resistance
    average = 1023 / average - 1;
    average = TEMPRESISTOR / average;
    
    // Copied code from https://arduinodiy.wordpress.com/2015/11/10/measuring-temperature-with-ntc-the-steinhart-hart-formula/
    float steinhart;
    steinhart = average / THERMISTORNOMINAL;          // (R/Ro)
    steinhart = log(steinhart);                       // ln(R/Ro)
    steinhart /= BCOEFFICIENT;                        // 1/B * ln(R/Ro)
    steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
    steinhart = 1.0 / steinhart;                      // Invert
    steinhart -= 273.15;

    temp = steinhart + OFFSETTEMP;;
}

void mosPWMSetup()
{   
    // The timer configuration was complex so I found this code snippet on some forum
    // Configure Timer 1 for PWM @ 25 kHz.
    TCCR1A = 0;            // undo the configuration done by...
    TCCR1B = 0;            // ...the Arduino core library
    TCNT1 = 0;             // reset timer
    TCCR1A = _BV(COM1A1)   // non-inverted PWM on ch. A
             | _BV(COM1B1) // same on ch; B
             | _BV(WGM11); // mode 10: ph. correct PWM, TOP = ICR1
    TCCR1B = _BV(WGM13)    // ditto
             | _BV(CS10);  // prescaler = 1
    ICR1 = 320;            // TOP = 320
    OCR1A = 320;

    //turn the PID on
    myPID.SetMode(AUTOMATIC);
    myPID.SetOutputLimits(0, 320);
    myPID.SetControllerDirection(REVERSE);
}

void mosPWMUpdate()
{

    //Specify the links and initial tuning parameters
    Setpoint = setTemp, Input = temp;

    myPID.Compute();

    OCR1A = Output;
}
