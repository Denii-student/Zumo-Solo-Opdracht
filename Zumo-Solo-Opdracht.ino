void setup()
{
  Serial.begin(9600);

  // --- STAP 1: Kalibreer automatisch op groen (draaiend)
  Serial.println("Kalibratie op GROEN gestart...");
  for (uint8_t i = 0; i < 120; i++)
  {
    if (i > 30 && i <= 90)
    {
      lijnvolger.spinLeft();  // Linksom draaien
    }
    else
    {
      lijnvolger.spinRight(); // Rechtsom draaien
    }

    gedeeldeSensor.calibrate();
    delay(20);
  }
  lijnvolger.stop();
  Serial.println("Kalibratie GROEN klaar. Zet de robot op zwart en druk op A...");

  // --- STAP 2: Wacht op knop A om zwart te calibreren
  while (!buttonA.getSingleDebouncedPress());

  Serial.println("Kalibratie op ZWART gestart. Beweeg handmatig of houd stil...");
  for (uint8_t i = 0; i < 100; i++)
  {
    gedeeldeSensor.calibrate();
    delay(20);
  }
  Serial.println("Kalibratie ZWART klaar.");

  // --- STAP 3: Wacht op knop B om te beginnen met rijden
  Serial.println("Zet de robot aan de start en druk op B...");
  while (!buttonB.getSingleDebouncedPress());
  Serial.println("Gestart met lijn volgen!");
}
