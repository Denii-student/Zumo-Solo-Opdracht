#include "LineFollower.h"
#include "ColorSensor.h"
#include "SumoBehavior.h"
#include <Zumo32U4.h>

// ✅ Gedeelde lijnsensor wordt aangemaakt in main
Zumo32U4LineSensors gedeeldeSensor;

// ✅ Klassen krijgen allebei toegang tot dezelfde sensor
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
    sumoGedrag.engage();             // Sumo modus: blok detecteren en duwen
  }
  else if (kleurSensor.detectBrown())
  {
    inSumoMode = true;               // Activeer sumo-modus
    lijnvolger.stop();               // Voor de zekerheid stoppen voor overgang
    delay(500);                      // Korte pauze voor overgang
  }
  else
  {
    lijnvolger.followLine();         // Volg lijn zolang bruin niet is gedetecteerd
  }
}
