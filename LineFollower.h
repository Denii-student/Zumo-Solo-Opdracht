#ifndef LINE_FOLLOWER_H
#define LINE_FOLLOWER_H

#include <Zumo32U4.h>

/*
 * Klasse: LineFollower
 * Doel: Laat de robot een lijn volgen met behulp van PID-regeling
 * Gebruikt een gedeelde lijnsensor en stuurt de motoren aan op basis van lijnpositie
 */
class LineFollower
{
public:
    LineFollower(Zumo32U4LineSensors& sharedSensors, uint16_t maxSpeed = 400);
    // Constructor: gebruikt gedeelde sensor en stelt max snelheid in (standaard 400)

    void calibrate();
    // Draait op eigen plek en kalibreert de lijnsensor

    void followLine();
    // Laat de robot een lijn volgen met een PID-regeling

    void stop();
    // Zet beide motoren stil

private:
    Zumo32U4LineSensors& lineSensors;
    // Referentie naar gedeelde lijnsensor (komt uit main)

    Zumo32U4Motors motors;
    // Zumo-motorcontroller

    static const uint8_t numSensors = 5;
    // Aantal sensoren in de lijnsensor-array

    unsigned int sensorValues[numSensors];
    // Array met huidige sensorwaarden (voor PID en debug)

    int16_t lastError = 0;
    // Laatste foutwaarde van lijnpositie (voor D-term)

    uint16_t maxSpeed;
    // Maximale motorsnelheid (standaard 400)
};

#endif
