#include "ColorSensor.h"

ColorSensor::ColorSensor()
{
  lineSensors.initFiveSensors();
}

bool ColorSensor::detectBrown()
{
  lineSensors.readCalibrated(sensorValues);

  uint16_t total = 0;
  for (uint8_t i = 0; i < numSensors; i++)
  {
    total += sensorValues[i];
  }

  uint16_t average = total / numSensors;

  if (average > brownMin && average < brownMax)
  {
    return true;  // Bruine lijn gedetecteerd
  }
  else
  {
    return false; // Geen bruine lijn
  }
}
