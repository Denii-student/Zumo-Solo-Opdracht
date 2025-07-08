#include "ColorSensor.h"

// Constructor die een gedeelde lijnsensor ontvangt (referentie)
ColorSensor::ColorSensor(Zumo32U4LineSensors& sharedSensors)
  : lineSensors(sharedSensors) // Koppel de referentie aan het interne veld
{
  // Geen initFiveSensors() hier, want dat is al gedaan bij LineFollower
}

bool ColorSensor::detectBrown()
{
  // Lees de sensorwaarden via de gedeelde sensor
  lineSensors.readLine(sensorValues);

  // Optioneel: print individuele waarden (debug)
  Serial.print("Sensoren: ");
  uint16_t total = 0;
  for (uint8_t i = 0; i < numSensors; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print(" ");
    total += sensorValues[i];
  }

  // Bereken gemiddelde waarde
  uint16_t average = total / numSensors;
  Serial.print("  Gemiddelde: ");
  Serial.println(average);

  // Controleer of het gemiddelde binnen het bruine bereik valt
  if (average > brownMin && average < brownMax)
  {
    return true;  // Bruine lijn gedetecteerd
  }
  else
  {
    return false; // Geen bruine lijn
  }
}
