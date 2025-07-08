#ifndef LINE_FOLLOWER_H
#define LINE_FOLLOWER_H

#include <Zumo32U4.h>

class LineFollower
{
public:
    LineFollower(uint16_t maxSpeed = 400);
    // Constructor: stelt maximale snelheid in (standaard 400)

    void calibrate();
    // Laat de robot heen en weer draaien en kalibreert de lijnsensoren

    void followLine();
    // Laat de robot de lijn volgen met een PID-regeling

private:
    Zumo32U4LineSensors lineSensors;
    // Lijnsensor-array van de Zumo (5 sensoren)

    Zumo32U4Motors motors;
    // Motorcontroller van de Zumo

    static const uint8_t numSensors = 5;
    // Aantal lijnsensoren op de Zumo

    unsigned int sensorValues[numSensors];
    // Gekalibreerde waarden van de lijnsensoren

    int16_t lastError = 0;
    // Laatste foutwaarde (voor de D-term van de PID-regeling)

    uint16_t maxSpeed;
    // Maximale snelheid van de motoren
};

#endif
