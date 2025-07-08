#include "SumoBehavior.h"

SumoBehavior::SumoBehavior()
{
  proxSensors.initThreeSensors(); // Activeer de linker + rechter IR-sensor
}

void SumoBehavior::engage()
{
  while (true)
  {
    searchAndPush();
  }
}

void SumoBehavior::searchAndPush()
{
  proxSensors.read(); // Lees linker & rechter sensor

  uint16_t left = proxSensors.countsLeftWithLeftLED();
  uint16_t right = proxSensors.countsRightWithRightLED();

  if (left > 3 && right > 3)
  {
    // Object recht voor robot
    motors.setSpeeds(200, 200);
  }
  else if (left > right)
  {
    // Object links → draai links
    motors.setSpeeds(-100, 100);
  }
  else if (right > left)
  {
    // Object rechts → draai rechts
    motors.setSpeeds(100, -100);
  }
  else
  {
    // Niets gedetecteerd → draai langzaam om te zoeken
    motors.setSpeeds(100, -100);
  }

  delay(100);
}
