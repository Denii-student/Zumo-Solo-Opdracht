#include "ColorSensor.h"

ColorSensor::ColorSensor()
{
  lineSensors.initFiveSensors();
}

bool ColorSensor::detectBrown()
{
  // Lees de sensorwaarden met readLine() i.p.v. readCalibrated()
  lineSensors.readLine(sensorValues);

  // Optioneel: print de individuele waarden (voor debuggen)
  Serial.print("Sensoren: ");
  uint16_t total = 0;
  for (uint8_t i = 0; i < numSensors; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print(" ");
    total += sensorValues[i];
  }

  // Bereken het gemiddelde
  uint16_t average = total / numSensors;
  Serial.print("  Gemiddelde: ");
  Serial.println(average);

  // Vergelijk met drempelwaarden voor bruin
  if (average > brownMin && average < brownMax)
  {
    return true;  // Bruine lijn gedetecteerd
  }
  else
  {
    return false; // Geen bruine lijn
  }
}
