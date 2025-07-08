#include "LineFollower.h"

LineFollower::LineFollower(Zumo32U4LineSensors& sharedSensors, uint16_t maxSpeed)
  : lineSensors(sharedSensors), maxSpeed(maxSpeed)
{
  lineSensors.initFiveSensors();
}

void LineFollower::calibrate()
{
  delay(1000);
  for (uint16_t i = 0; i < 100; i++)
  {
    lineSensors.calibrate(); // Beweeg handmatig over zwarte lijn
    delay(20);
  }
}

void LineFollower::followLine()
{
  int16_t position = lineSensors.readLine(sensorValues);
  int16_t error = position - 2000;
  int16_t speedDifference = error / 6 + 4 * (error - lastError);
  lastError = error;

  int16_t leftSpeed = (int16_t)maxSpeed + speedDifference;
  int16_t rightSpeed = (int16_t)maxSpeed - speedDifference;

  leftSpeed = constrain(leftSpeed, 0, (int16_t)maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, (int16_t)maxSpeed);

  motors.setSpeeds(leftSpeed, rightSpeed);
}

void LineFollower::stop()
{
  motors.setSpeeds(0, 0);
}
