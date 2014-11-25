#ifndef PID_CONTROL_ALGORITHM_H
#define PID_CONTROL_ALGORITHM_H

#include "ControlAlgorithm.h"
#include "Sensor.h"
#include "Drive.h"

class PIDControlAlgorithm : 
public ControlAlgorithm
{
private:
  double pasterr;
  double p, i, d, w;
  double perr, ierr, derr;
  double maxspd;
public:
  PIDControlAlgorithm(Sensor* inputsensor, Drive* outputdrive, double proportional, double integral, double derivative, double weight, double speed);
  void process();
};

#endif

