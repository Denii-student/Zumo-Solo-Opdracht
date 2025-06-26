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

    Zumo32U4ButtonA buttonA;
    // Knop A wordt gebruikt om de calibratie te starten

    Zumo32U4OLED display;
    // OLED-scherm voor weergave van sensorgegevens

    static const uint8_t numSensors = 5;
    // Aantal lijnsensoren op de Zumo

    unsigned int sensorValues[numSensors];
    // Gekalibreerde waarden van de lijnsensoren

    int16_t lastError = 0;
    // Laatste foutwaarde (voor de D-term van de PID-regeling)

    uint16_t maxSpeed;
    // Maximale snelheid van de motoren

    void loadCustomCharacters();
    // Laadt grafiek-symbolen in voor het OLED-scherm

    void printBar(uint8_t height);
    // Tekent één balk op het OLED-scherm (hoogte 0–8)

    void showSensorReadings();
    // Toont een live grafiek van sensorwaarden op het OLED-scherm
};

#endif
