#include "LineFollower.h"

LineFollower lijnvolger;

void setup()
{
  lijnvolger.calibrate();
}

void loop()
{
  lijnvolger.followLine();
}

