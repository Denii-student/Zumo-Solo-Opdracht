#include "LineFollower.h"
#include "ColorSensor.h"

// Maak objecten aan voor lijnvolging en kleurdetectie
LineFollower lijnvolger;
ColorSensor kleurSensor;

void setup()
{
  Serial.begin(9600);              // Start de seriële monitor voor debugging
  lijnvolger.calibrate();          // Start de calibratie op de groene lijn
}

void loop()
{
  // Als een bruine lijn wordt gedetecteerd:
  if (kleurSensor.detectBrown()) {
    lijnvolger.stop();             // Stop de robot via publieke methode
    delay(10000);                  // Wacht 10 seconden zodat je het kunt zien
  }
  else {
    lijnvolger.followLine();       // Volg de lijn als er geen bruin is
  }
}
