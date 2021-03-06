#ifndef DRIVE_H
#define DRIVE_H
#include "../Sensors/Sensor.h"

class Drive
{
protected:
    Sensor* sensor;
    double lspeed, rspeed;
public:
    virtual void drive(double spd){}
    virtual void setlspeed(double newlspeed){ lspeed = newlspeed; }
    virtual void getlspeed(double &tblspeed){ tblspeed = lspeed; }
    virtual void setrspeed(double newrspeed){ rspeed = newrspeed; }
    virtual void getrspeed(double &tbrspeed){ tbrspeed = rspeed; }
};

#endif