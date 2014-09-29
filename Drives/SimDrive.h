#ifndef SIM_DRIVE_H
#define SIM_DRIVE_H

#include "Drive.h"
#include "../Simulation/SimBridge.h"

class SimDrive : public Drive
{
private:
    SimBridge* bridge;
    double lspeed, rspeed;
public:
    SimDrive(SimBridge* simbridge);
    void setlspeed(double newlspeed);
    void getlspeed(double &tblspeed);
    void setrspeed(double newrspeed);
    void getrspeed(double &tbrspeed);
    void drive();
};

#endif