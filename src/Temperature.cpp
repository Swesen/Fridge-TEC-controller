#include <Arduino.h>
#include "Defines.h"
#include "Temperature.h"

// internal variables


Temperature::Temperature(char thermistorPin, unsigned char smoothing, unsigned int resistorValue, unsigned int nominalThermistorResistance, int nominalTemperature, int betaCoefficient) 
{
    this->thermistorPin = thermistorPin;
    this->smoothing = smoothing;
    this->resistorValue = resistorValue;
    this->nominalThermistorResistance = nominalThermistorResistance;
    this->nominalTemperature = nominalTemperature;
    this->betaCoefficient = betaCoefficient;

    // allocate memory for multiple samples
    samples = (int *)calloc(smoothing, sizeof(int));

    pinMode(thermistorPin, INPUT);
}

Temperature::~Temperature() 
{
    free(samples);
}

char Temperature::getTemperature() 
{
    // tage a new reading and add to samples
    samples[currentIndex] = analogRead(thermistorPin);

    // make sure the next index is within range
    if (currentIndex >= smoothing)
    {
        currentIndex = 0;
    }
    else
    {
        currentIndex++;
    }

    // average all the samples out
    float average = 0;
    for (int i = 0; i < smoothing; i++)
    {
        average += samples[i];
    }
    average /= smoothing;

    // convert the value to resistance
    average = resistorValue / (1024 / average + 1);

    // convert the readings into celsius
    return 1.0 /(log(average / nominalThermistorResistance) / betaCoefficient + (1.0 / (nominalTemperature + 273.15))) - 273.15;
}


