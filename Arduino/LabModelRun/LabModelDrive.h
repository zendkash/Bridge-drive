#ifndef LAB_MODEL_DRIVE_H
#define LAB_MODEL_DRIVE_H
#include "Drive.h"
#include "Sensor.h"

class LabModelDrive: public Drive
{
protected:
    double wheelSize;
    int countsPerRot;
public:
    LabModelDrive(Sensor* newsensor, double wSize, int numcounts);
    virtual void drive();
};

#endif
