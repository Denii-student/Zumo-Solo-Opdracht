#ifndef COLOR_SENSOR_H
#define COLOR_SENSOR_H

#include <Zumo32U4.h>

/*
 * Klasse: ColorSensor
 * Doel: Detecteert een bruine lijn onder de robot
 * Werkt op basis van reflectiewaarden van de 5 lijnsensoren van de Zumo
 * Detectie is gebaseerd op gemiddelde reflectie én het aantal actieve sensoren
 */
class ColorSensor
{
public:
    ColorSensor(Zumo32U4LineSensors& sharedSensors);
    // Constructor: gebruikt gedeelde lijnsensor die al gekalibreerd is via LineFollower

    bool detectBrown();
    // Retourneert true als een horizontale bruine lijn onder de robot wordt herkend

private:
    Zumo32U4LineSensors& lineSensors;
    // Referentie naar gedeelde lijnsensor-array

    static const uint8_t numSensors = 5;
    // Aantal lijnsensoren op de Zumo

    unsigned int sensorValues[numSensors];
    // Sensorwaarden van de huidige meting

    uint16_t brownMin = 300;
    uint16_t brownMax = 700;
    // Op basis van metingen: gemiddelde waarde voor bruin ligt tussen 250 en 330
};

#endif
