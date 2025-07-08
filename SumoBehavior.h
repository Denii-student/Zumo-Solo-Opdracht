#ifndef SUMO_BEHAVIOR_H
#define SUMO_BEHAVIOR_H

#include <Zumo32U4.h>

class SumoBehavior
{
public:
    SumoBehavior();
    void engage(); // Start actief duwen

private:
    Zumo32U4Motors motors;
    Zumo32U4ProximitySensors proxSensors;

    void searchAndPush(); // detecteer blok en duw
};

#endif
