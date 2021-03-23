#ifndef __TEMPERATURE_H__
#define __TEMPERATURE_H__

class Temperature
{
private:
    uint8_t thermistorPin;
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
    Temperature(uint8_t thermistorPin, byte smoothing, unsigned int resistorValue, unsigned int nominalThermistorResistance, int nominalTemperature, int betaCoefficient);
    ~Temperature();

    void start();
    double getTemperature();
};
#endif // __TEMPERATURE_H__