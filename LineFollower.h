#ifndef LINE_FOLLOWER_H
#define LINE_FOLLOWER_H

#include <Zumo32U4.h>

class LineFollower
{
public:
    LineFollower(Zumo32U4LineSensors& sharedSensors, uint16_t maxSpeed = 400);
    void calibrate();    // Kalibreert op zwarte lijn
    void followLine();   // Volgt de lijn met PID
    void stop();         // Stopt beide motoren

private:
    Zumo32U4LineSensors& lineSensors;
    Zumo32U4Motors motors;

    static const uint8_t numSensors = 5;
    unsigned int sensorValues[numSensors];

    int16_t lastError = 0;
    uint16_t maxSpeed;
};

#endif
