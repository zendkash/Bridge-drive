#ifndef LAB_MODEL_DRIVE_H
#define LAB_MODEL_DRIVE_H
#include "Drive.h"
#include "Sensor.h"
#include "Arduino.h"
#include <SPI.h>

class FSPDrive: public Drive
{
protected:
public:
    FSPDrive(Sensor* newsensor, double newnomspd);
    virtual void drive(int nomspeed, bool forward);
};

#endif
