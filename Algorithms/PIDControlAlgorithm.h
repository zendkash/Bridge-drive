#ifndef PID_CONTROL_ALGORITHM_H
#define PID_CONTROL_ALGORITHM_H

#include "ControlAlgorithm.h"
#include "../Sensors/Sensor.h"
#include "../Drives/Drive.h"

class PIDControlAlgorithm : public ControlAlgorithm
{
private:
    double pasterr;
public:
    PIDControlAlgorithm(Sensor* inputsensor, Drive* outputdrive);

};

#endif