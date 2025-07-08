#ifndef COLOR_SENSOR_H
#define COLOR_SENSOR_H

#include <Zumo32U4.h>

class ColorSensor
{
public:
    ColorSensor(Zumo32U4LineSensors& sharedSensors);
    bool detectBrown();  // Retourneert true als bruine lijn is gezien

private:
    Zumo32U4LineSensors& lineSensors;

    static const uint8_t numSensors = 5;
    unsigned int sensorValues[numSensors];

    // Afkomstig uit jouw testen
    uint16_t brownMin = 300;
    uint16_t brownMax = 700;
};

#endif
