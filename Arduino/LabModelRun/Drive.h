#ifndef DRIVE_H
#define DRIVE_H
#include "Sensor.h"

class Drive
{
protected:
    Sensor* sensor;
    double nomspd, lspd, rspd;
public:
    Drive(Sensor* newsensor){sensor = newsensor; lspd = 0; rspd = 0; nomspd = 0;}
    virtual void drive(double spd){}
    
    virtual void setnomspd(double newnomspd){ nomspd = newnomspd; }
    virtual void getnomspd(double &tbnomspd){ tbnomspd = nomspd; }
    virtual void setlspd(double newlspd){ lspd = newlspd; }
    virtual void getlspd(double &tblspd){ tblspd = lspd; }
    virtual void setrspd(double newrspd){ rspd = newrspd; }
    virtual void getrspd(double &tbrspd){ tbrspd = rspd; }
};

#endif
