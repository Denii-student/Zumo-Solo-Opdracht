#include <Zumo32U4.h>
#include "LineFollower.h"
#include "ColorSensor.h"

Zumo32U4LineSensors gedeeldeSensor;
LineFollower lijnvolger(gedeeldeSensor);
ColorSensor kleurSensor(gedeeldeSensor);

void setup()
{
  Serial.begin(9600);
  Serial.println("Kalibratie op zwart gestart...");

  delay(1000);
  for (uint8_t i = 0; i < 100; i++)
  {
    gedeeldeSensor.calibrate();
    delay(20);
  }

  Serial.println("Kalibratie voltooid. Start met lijn volgen.");
}

void loop()
{
  if (kleurSensor.detectBrown())
  {
    lijnvolger.stop();
    Serial.println("Bruine lijn gedetecteerd, robot stopt.");
    delay(10000); // zichtbare stop
  }
  else
  {
    lijnvolger.followLine();
  }
}
