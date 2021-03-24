#include <Arduino.h>
#include "Defines.h"
#include "Temperature.h"

// internal variables

Temperature::Temperature(uint8_t thermistorPin, byte smoothing, unsigned int resistorValue, unsigned int nominalThermistorResistance, int nominalTemperature, int betaCoefficient)
{
    this->thermistorPin = thermistorPin;
    this->smoothing = smoothing;
    this->resistorValue = resistorValue;
    this->nominalThermistorResistance = nominalThermistorResistance;
    this->nominalTemperature = nominalTemperature;
    this->betaCoefficient = betaCoefficient;

    // allocate memory for multiple samples
    samples = (int *)calloc(smoothing, sizeof(int));
}

Temperature::~Temperature()
{
    free(samples);
}

void Temperature::start()
{
    pinMode(A1, INPUT);
}

double Temperature::getTemperature()
{
    // tage a new reading and add to samples
    samples[currentIndex] = analogRead(A1);

    // make sure the next index is within range
    if (currentIndex >= smoothing - 1)
    {
        currentIndex = 0;
    }
    else
    {
        currentIndex++;
    }

    // average all the samples out
    double average = 0;
    for (int i = 0; i < smoothing; i++)
    {
        average += samples[i];
    }
    average /= smoothing;

    // convert the value to resistance
    average = resistorValue / (1023 / average - 1);

    // convert the readings into celsius
    double steinhart;
    steinhart = average / nominalThermistorResistance; // (R/Ro)
    steinhart = log(steinhart);                        // ln(R/Ro)
    steinhart /= betaCoefficient;                      // 1/B * ln(R/Ro)
    steinhart += 1.0 / (nominalTemperature + 273.15);  // + (1/To)
    steinhart = 1.0 / steinhart;                       // Invert
    steinhart -= 273.15;

    return steinhart;
}
