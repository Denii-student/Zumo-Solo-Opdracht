#include "ColorSensor.h"

ColorSensor::ColorSensor()
{
  // Initialiseer de 5 lijnsensoren van de Zumo
  lineSensors.initFiveSensors();
}

bool ColorSensor::detectBrown()
{
  // Lees gekalibreerde sensorwaarden in de array 'sensorValues'
  lineSensors.readCalibrated(sensorValues);

  // Bereken het gemiddelde van de 5 sensorwaarden
  uint16_t total = 0;
  for (uint8_t i = 0; i < numSensors; i++)
  {
    total += sensorValues[i];
  }
  uint16_t average = total / numSensors;

  // Controleer of de gemiddelde waarde binnen het bruine bereik valt
  if (average > brownMin && average < brownMax)
  {
    return true;  // Bruine lijn gedetecteerd
  }
  else
  {
    return false; // Geen bruine lijn
  }
}
