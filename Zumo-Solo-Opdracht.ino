#include "LineFollower.h"
#include "ColorSensor.h"

// Maak objecten aan voor lijnvolging en kleurdetectie
LineFollower lijnvolger;
ColorSensor kleurSensor;

void setup()
{
  // Start de calibratie op de groene lijn (of zwart als je dat gebruikt)
  lijnvolger.calibrate();
}

void loop()
{
  // Als een bruine lijn wordt gedetecteerd:
  if (kleurSensor.detectBrown()) {
    // Stop de robot via de publieke methode
    lijnvolger.stop();

    // Pauze zodat je ziet dat hij gestopt is (10 seconden)
    delay(10000);
  }
  else {
    // Anders gewoon de lijn volgen
    lijnvolger.followLine();
  }
}
