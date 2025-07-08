#include "LineFollower.h"
#include "ColorSensor.h"
#include <Zumo32U4.h>

// ✅ Gedeelde lijnsensor wordt aangemaakt in main
Zumo32U4LineSensors gedeeldeSensor;

// ✅ Klassen krijgen allebei toegang tot dezelfde sensor
LineFollower lijnvolger(gedeeldeSensor);
ColorSensor kleurSensor(gedeeldeSensor);

void setup()
{
  Serial.begin(9600); // Start seriële communicatie voor debug
  lijnvolger.calibrate(); // Kalibreer op groene lijn (herkent dan ook zwart)
}

void loop()
{
  // Check of robot op een bruine lijn staat
  if (kleurSensor.detectBrown())
  {
    lijnvolger.stop(); // Stop robot
    delay(10000);      // Pauze van 10 seconden om dit zichtbaar te maken
  }
  else
  {
    lijnvolger.followLine(); // Normaal lijngedrag met PID
  }
}
