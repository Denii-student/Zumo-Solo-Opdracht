#include <Zumo32U4.h>
#include "LineFollower.h"
#include "ColorSensor.h"

// === Gedeelde lijnsensor en knoppen aanmaken ===
Zumo32U4LineSensors gedeeldeSensor;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;

// === Objecten die gebruik maken van dezelfde sensor ===
LineFollower lijnvolger(gedeeldeSensor);
ColorSensor kleurSensor(gedeeldeSensor);

void setup()
{
  Serial.begin(9600);

  // === STAP 1: Automatische kalibratie op GROEN ===
  Serial.println("Stap 1: Kalibratie op GROEN gestart...");
  delay(1000);

  for (uint8_t i = 0; i < 120; i++)
  {
    if (i > 30 && i <= 90)
    {
      lijnvolger.spinLeft();  // Linksom draaien
    }
    else
    {
      lijnvolger.spinRight(); // Rechtsom draaien
    }

    gedeeldeSensor.calibrate();
    delay(20);
  }

  lijnvolger.stop();
  Serial.println("Kalibratie GROEN voltooid ✅");

  // === STAP 2: Wachten op knop A voor zwart-kalibratie ===
  Serial.println("Zet robot op ZWART en druk op A...");
  while (!buttonA.getSingleDebouncedPress());

  Serial.println("Stap 2: Kalibratie op ZWART gestart...");
  for (uint8_t i = 0; i < 100; i++)
  {
    gedeeldeSensor.calibrate();
    delay(20);
  }
  Serial.println("Kalibratie ZWART voltooid ✅");

  // === STAP 3: Wachten op knop B om te starten ===
  Serial.println("Zet robot aan de START van de lijn en druk op B...");
  while (!buttonB.getSingleDebouncedPress());

  Serial.println("Start met lijn volgen...");
}

void loop()
{
  // Stop bij bruine lijn
  if (kleurSensor.detectBrown())
  {
    lijnvolger.stop();
    Serial.println("BRUINE LIJN GEDTECTEERD – robot stopt.");
    delay(10000); // Pauze zodat je het kunt zien
  }
  else
  {
    lijnvolger.followLine();
  }
}
