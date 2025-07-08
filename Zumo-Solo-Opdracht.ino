#include "LineFollower.h"
#include "ColorSensor.h"
#include "SumoBehavior.h"
#include <Zumo32U4.h>

// ✅ Gedeelde lijnsensor wordt aangemaakt in main
Zumo32U4LineSensors gedeeldeSensor;

// ✅ Klassen krijgen toegang tot dezelfde sensor
LineFollower lijnvolger(gedeeldeSensor);
ColorSensor kleurSensor(gedeeldeSensor);
SumoBehavior sumoGedrag;

bool inSumoMode = false;

void setup()
{
  Serial.begin(9600);                 // Debug via Serial Monitor
  lijnvolger.calibrate();            // Kalibreer op zwarte lijn
}

void loop()
{
  if (inSumoMode)
  {
    sumoGedrag.engage();             // Start sumo-modus éénmalig
    inSumoMode = false;              // Zorg dat engage() niet herhaald wordt
  }
  else if (kleurSensor.detectBrown())
  {
    inSumoMode = true;               // Zet sumo-modus actief
    lijnvolger.stop();               // Stop eerst lijnvolging
    delay(500);                      // Korte stabilisatiepauze
  }
  else
  {
    lijnvolger.followLine();         // Volg lijn met PID
  }
}
