#include "LineFollower.h"

// Constructor: ontvangt gedeelde lijnsensor en stelt max snelheid in
LineFollower::LineFollower(Zumo32U4LineSensors& sharedSensors, uint16_t maxSpeed)
  : lineSensors(sharedSensors), maxSpeed(maxSpeed)
{
  lineSensors.initFiveSensors(); // Initialiseer de sensorarray
}

void LineFollower::calibrate()
{
  delay(1000); // Wacht even voor calibratie begint

  // Calibratie: draai 2 rondjes (120 stappen) en neem sensorwaarden op
  for (uint16_t i = 0; i < 120; i++)
  {
    if (i > 30 && i <= 90)
    {
      motors.setSpeeds(-200, 200); // Draai linksom
    }
    else
    {
      motors.setSpeeds(200, -200); // Draai rechtsom
    }

    lineSensors.calibrate(); // Registreer sensorwaarden
  }

  motors.setSpeeds(0, 0); // Stop na calibratie
}

void LineFollower::followLine()
{
  // Lees lijnpositie: 0 = helemaal links, 4000 = helemaal rechts, 2000 = midden
  int16_t position = lineSensors.readLine(sensorValues);

  // Bereken afwijking van het midden
  int16_t error = position - 2000;

  // Bereken snelheidsverschil met PID (alleen P & D)
  int16_t speedDifference = error / 4 + 6 * (error - lastError);
  lastError = error;

  // Stel linker- en rechtersnelheid in
  int16_t leftSpeed = (int16_t)maxSpeed + speedDifference;
  int16_t rightSpeed = (int16_t)maxSpeed - speedDifference;

  // Beperk snelheden tot geldige range
  leftSpeed = constrain(leftSpeed, 0, (int16_t)maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, (int16_t)maxSpeed);

  // Pas motoren aan
  motors.setSpeeds(leftSpeed, rightSpeed);
}

void LineFollower::stop()
{
  // Zet beide motoren stil
  motors.setSpeeds(0, 0);
}
