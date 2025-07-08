#include "ColorSensor.h"

ColorSensor::ColorSensor(Zumo32U4LineSensors& sharedSensors)
  : lineSensors(sharedSensors)
{
}

bool ColorSensor::detectBrown()
{
  lineSensors.readLine(sensorValues);

  uint16_t total = 0;
  for (uint8_t i = 0; i < numSensors; i++)
  {
    total += sensorValues[i];
  }

  uint16_t average = total / numSensors;

  return (average > brownMin && average < brownMax);
}
