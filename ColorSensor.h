#ifndef COLOR_SENSOR_H
#define COLOR_SENSOR_H

#include <Zumo32U4.h>

/*
 * Klasse: ColorSensor
 * Doel: Detecteert een bruine lijn onder de robot
 * Werkt op basis van reflectiewaarden van de 5 lijnsensoren van de Zumo
 */
class ColorSensor
{
public:
    ColorSensor();
    // Constructor: initialiseert de lijnsensoren

    bool detectBrown();
    // Leest sensorwaarden en bepaalt of de robot boven een bruine lijn staat

private:
    Zumo32U4LineSensors lineSensors;
    // Lijnsensor-array van de Zumo (5 sensoren)

    static const uint8_t numSensors = 5;
    // Aantal lijnsensoren op de Zumo

    unsigned int sensorValues[numSensors];
    // Array met gekalibreerde reflectiewaarden van de sensoren

    uint16_t brownMin = 300;
    uint16_t brownMax = 700;
    // Verwachte drempelwaarden voor een bruine lijn (kan worden aangepast)
};

#endif
