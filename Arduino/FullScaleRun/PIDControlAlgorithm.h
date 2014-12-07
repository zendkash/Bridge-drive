#ifndef PID_CONTROL_ALGORITHM_H
#define PID_CONTROL_ALGORITHM_H

#include "ControlAlgorithm.h"
#include "Sensor.h"
#include "Drive.h"

#define FORWARD true

class PIDControlAlgorithm : 
public ControlAlgorithm
{
private:
  double pasterr;
  double p, i, d, w;
  double perr, ierr, derr;
  double minspd, maxspd;
  double frontscl, rearscl;
public:
  PIDControlAlgorithm(Sensor* inputsensor, Drive* outputdrive, double proportional, double integral, double derivative, double weight, double frontscale, double rearscale, double minspeed, double maxspeed);
  void process(bool direction);
};

#endif

