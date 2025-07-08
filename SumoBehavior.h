#ifndef SUMO_BEHAVIOR_H
#define SUMO_BEHAVIOR_H

#include <Zumo32U4.h>

/*
 * Klasse: SumoBehavior
 * Doel: Zoek en duw het blok uit de cirkel met behulp van infraroodsensoren.
 */
class SumoBehavior
{
public:
    SumoBehavior();
    void engage();           // Start actief zoeken en duwen
    bool isFinished();       // Geeft aan of sumo-actie is voltooid

private:
    Zumo32U4Motors motors;
    Zumo32U4ProximitySensors proxSensors;
    Zumo32U4LineSensors lineSensors;

    bool finished = false;   // Vlag om te onthouden of robot klaar is
};

#endif // SUMO_BEHAVIOR_H
