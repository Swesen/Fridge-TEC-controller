#ifndef __TEMPERATURE_H__
#define __TEMPERATURE_H__

class Temperature
{
private:
    char thermistorPin;
    int currentIndex = 0;
    int *samples;
    byte smoothing;

    // the resistor used as a divider
    unsigned int resistorValue;

    // thermistor values
    // the resistance of the thermistor at nominalTemperature
    unsigned int nominalThermistorResistance;
    int nominalTemperature;
    int betaCoefficient;

public:
    Temperature(char thermistorPin, byte smoothing, unsigned int resistorValue, unsigned int nominalThermistorResistance, int nominalTemperature, int betaCoefficient);
    ~Temperature();

    float getTemperature();
};
#endif // __TEMPERATURE_H__