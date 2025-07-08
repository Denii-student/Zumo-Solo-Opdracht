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
    ColorSensor(Zumo32U4LineSensors& sharedSensors);
    // Constructor: gebruikt gedeelde lijnsensor (al gekalibreerd via LineFollower)

    bool detectBrown();
    // Leest sensorwaarden en bepaalt of de robot boven een bruine lijn staat

private:
    Zumo32U4LineSensors& lineSensors;
    // Referentie naar gedeelde lijnsensor-array

    static const uint8_t numSensors = 5;
    // Aantal lijnsensoren op de Zumo

    unsigned int sensorValues[numSensors];
    // Array met reflectiewaarden van de sensoren

    uint16_t brownMin = 300;
    uint16_t brownMax = 700;
    // Drempelwaarden voor bruine lijn (aanpasbaar)
};

#endif
