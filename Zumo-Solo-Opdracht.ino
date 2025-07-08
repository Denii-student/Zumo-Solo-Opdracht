#include <Zumo32U4.h>
#include "LineFollower.h"
#include "ColorSensor.h"

Zumo32U4LineSensors gedeeldeSensor;
Zumo32U4ButtonA buttonA;

LineFollower lijnvolger(gedeeldeSensor);
ColorSensor kleurSensor(gedeeldeSensor);

bool inSumoMode = false;

void setup()
{
  Serial.begin(9600);
  Serial.println("Plaats robot op zwarte lijn en druk op knop A");

  while (!buttonA.getSingleDebouncedPress());

  lijnvolger.calibrate();
  Serial.println("Kalibratie voltooid ✅");
}

void loop()
{
  if (inSumoMode)
  {
    // ➕ Hier komt later jouw sumo-mode gedrag
    Serial.println("➤ SUMO MODE ACTIEF");
    // bijv: draai en duw
    return;
  }

  if (kleurSensor.detectBrown())
  {
    lijnvolger.stop();
    Serial.println("Bruine lijn gedetecteerd, overschakelen naar sumo...");
    delay(1000);
    inSumoMode = true;
  }
  else
  {
    lijnvolger.followLine();
  }
}
