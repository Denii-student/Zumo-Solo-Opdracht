#include "LineFollower.h"

LineFollower::LineFollower(uint16_t maxSpeed)
  : maxSpeed(maxSpeed) // Slaat de maximale snelheid op
{
  lineSensors.initFiveSensors(); // Initialiseer de 5 lijnsensoren
  loadCustomCharacters();        // Laad de grafiek-symbolen voor het OLED-display
}

void LineFollower::calibrate()
{
  display.clear();
  display.print(F("Calibreren..."));

  delay(1000); // Kleine pauze voor de calibratie begint

  // Robot draait 2 rondjes (120 stappen), wisselend links/rechts
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

    lineSensors.calibrate(); // Neem sensorwaarden op voor calibratie
  }

  motors.setSpeeds(0, 0); // Stop na calibratie

  showSensorReadings(); // Laat gekalibreerde waarden zien op OLED tot knop A wordt ingedrukt
}

void LineFollower::followLine()
{
  // Lees de positie van de lijn (2000 = midden)
  int16_t position = lineSensors.readLine(sensorValues);

  // Bereken fout tussen werkelijke en gewenste positie
  int16_t error = position - 2000;

  // PID-regeling: P-term (1/4) + D-term (6 × verschil in error)
  int16_t speedDifference = error / 4 + 6 * (error - lastError);

  lastError = error; // Sla huidige error op voor volgende loop

  // Stel motorsnelheden in
  int16_t leftSpeed = (int16_t)maxSpeed + speedDifference;
  int16_t rightSpeed = (int16_t)maxSpeed - speedDifference;

  // Zorg dat de snelheid binnen 0 en maxSpeed blijft
  leftSpeed = constrain(leftSpeed, 0, (int16_t)maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, (int16_t)maxSpeed);

  motors.setSpeeds(leftSpeed, rightSpeed); // Zet motors aan
}

void LineFollower::loadCustomCharacters()
{
  static const char levels[] PROGMEM = {
    0, 0, 0, 0, 0, 0, 0,
    63, 63, 63, 63, 63, 63, 63
  };

  for (uint8_t i = 0; i < 7; i++)
  {
    display.loadCustomCharacter(levels + i, i);
  }
}

void LineFollower::printBar(uint8_t height)
{
  if (height > 8) { height = 8; }

  const char barChars[] = {' ', 0, 1, 2, 3, 4, 5, 6, (char)255};
  display.print(barChars[height]); // Teken staaf op OLED
}

void LineFollower::showSensorReadings()
{
  display.clear();

  // Laat staafgrafieken zien tot knop A wordt ingedrukt
  while (!buttonA.getSingleDebouncedPress())
  {
    lineSensors.readCalibrated(sensorValues);

    display.gotoXY(0, 0);
    for (uint8_t i = 0; i < numSensors; i++)
    {
      uint8_t barHeight = map(sensorValues[i], 0, 1000, 0, 8);
      printBar(barHeight);
    }
  }

  display.clear();
}
