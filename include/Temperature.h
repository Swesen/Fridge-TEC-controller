#ifndef __TEMPERATURE_H__
#define __TEMPERATURE_H__

class Temperature
{
private:
    char thermistorPin;
    int currentIndex = 0;
    int *samples;
    unsigned char smoothing;

    // the resistor used as a divider
    unsigned int resistorValue;

    // thermistor values
    // the resistance of the thermistor at nominalTemperature
    unsigned int nominalThermistorResistance;
    int nominalTemperature;
    int betaCoefficient;

public:
    Temperature(char thermistorPin, unsigned char smoothing, unsigned int resistorValue, unsigned int nominalThermistorResistance, int nominalTemperature, int betaCoefficient);
    ~Temperature();

    char getTemperature();
};
#endif // __TEMPERATURE_H__