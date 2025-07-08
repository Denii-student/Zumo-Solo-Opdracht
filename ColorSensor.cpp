#include "ColorSensor.h"

// Constructor die een gedeelde lijnsensor ontvangt (referentie)
ColorSensor::ColorSensor(Zumo32U4LineSensors& sharedSensors)
  : lineSensors(sharedSensors) // Koppel de referentie aan het interne veld
{
  // Geen initFiveSensors() hier — dat doet LineFollower al
}

bool ColorSensor::detectBrown()
{
  // Lees de sensorwaarden via de gedeelde sensor (ongekalibreerd voor ruwe reflectiewaarden)
  lineSensors.read(sensorValues);

  uint16_t total = 0;
  uint8_t bruineSensoren = 0;

  // Tel de som en hoeveel sensoren binnen het bruine bereik vallen
  for (uint8_t i = 0; i < numSensors; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print(" ");
    total += sensorValues[i];

    if (sensorValues[i] >= brownMin && sensorValues[i] <= brownMax)
    {
      bruineSensoren++;
    }
  }

  uint16_t average = total / numSensors;

  Serial.print("  Gemiddelde: ");
  Serial.print(average);
  Serial.print("  Bruine sensoren: ");
  Serial.println(bruineSensoren);

  // Detecteer alleen bruin als minstens 4 sensoren in het bereik vallen
  if (average >= brownMin && average <= brownMax && bruineSensoren >= 4)
  {
    return true;  // BRUINE LIJN GEDTECTEERD
  }

  return false; // Geen bruine lijn
}
