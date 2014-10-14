#ifndef PID_CONTROL_ALGORITHM_H
#define PID_CONTROL_ALGORITHM_H

#include "ControlAlgorithm.h"
#include "../Sensors/Sensor.h"
#include "../Drives/Drive.h"

class PIDControlAlgorithm : public ControlAlgorithm
{
private:
    double pasterr;
    double p, i, d;
    double perr, ierr, derr;
    double spd;
public:
    PIDControlAlgorithm(Sensor* inputsensor, Drive* outputdrive, double proportional, double integral, double derivative, double speed);
    void process();
};

#endif