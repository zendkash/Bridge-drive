#ifndef SIM_DRIVE_H
#define SIM_DRIVE_H

#include "Drive.h"
#include "../Simulation/SimBridge.h"

class SimDrive : public Drive
{
private:
    SimBridge* bridge;
    double speed;
public:
    SimDrive(SimBridge* simbridge);
    void setspeed();
    void getspeed();
};

#endif