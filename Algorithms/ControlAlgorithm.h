#ifndef CONTROL_ALGORITHM_H
#define CONTROL_ALGORITHM_H

#include "../Sensors/Sensor.h"
#include "../Drives/Drive.h"

class ControlAlgorithm
{
protected:
    Sensor* sensor;
    Drive* drive;
public:
    ControlAlgorithm(Sensor* sens, Drive* drv);
    virtual void process(){}
};

#endif