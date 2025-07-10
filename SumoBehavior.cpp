#include "SumoBehavior.h"

SumoBehavior::SumoBehavior()
{
  proxSensors.initThreeSensors();
  lineSensors.initFiveSensors();  // Initialiseer lijnsensoren voor zwarte randdetectie
  finished = false;
}

void SumoBehavior::engage()
{
  if (finished) return; // voorkom dat engage opnieuw draait

  // Stap 1: Rijd ±20 cm rechtdoor
  motors.setSpeeds(300, 300);
  delay(2000);
  motors.setSpeeds(0, 0);

  // Stap 2: Draai 360 graden in stapjes en kijk wanneer object wordt gezien
  for (uint16_t i = 0; i < 36; i++)  // 36 × 100ms ≈ 360°
  {
    proxSensors.read();
    uint16_t front = proxSensors.countsFrontWithLeftLeds();

    Serial.print("IR front: ");
    Serial.println(front);

    if (front > 3)
    {
      delay(100);
      motors.setSpeeds(400, 400);  // Ga direct op blok af
      break;
    }

    // Geen object? Draai langzaam door
    motors.setSpeeds(300, -300);
    delay(100);
  }

  // Stap 3: Rijden richting object en corrigeren tot zwarte lijn
  while (true)
  {
    proxSensors.read();
    uint16_t left = proxSensors.countsLeftWithLeftLeds();
    uint16_t right = proxSensors.countsRightWithRightLeds();

    int16_t error = right - left;
    int16_t baseSpeed = 300;
    int16_t turnSpeed = error * 15;

    int16_t leftSpeed = constrain(baseSpeed - turnSpeed, 0, 400);
    int16_t rightSpeed = constrain(baseSpeed + turnSpeed, 0, 400);

    motors.setSpeeds(leftSpeed, rightSpeed);

    // Zwarte lijn detectie
    unsigned int reflectie[5];
    lineSensors.read(reflectie);

    uint16_t gemiddelde = 0;
    for (uint8_t i = 0; i < 5; i++)
    {
      gemiddelde += reflectie[i];
    }
    gemiddelde /= 5;

    Serial.print("Reflectie gemiddelde: ");
    Serial.println(gemiddelde);

    if (gemiddelde > 700)  // Grens voor zwart
    {
      motors.setSpeeds(0, 0);
      finished = true; // Markeer als afgerond
      break;
    }

    delay(50);
  }
}

bool SumoBehavior::isFinished()
{
  return finished;
}
