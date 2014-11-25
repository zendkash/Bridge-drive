#ifndef CONTROL_ALGORITHM_H
#define CONTROL_ALGORITHM_H

#include "Sensor.h"
#include "Drive.h"

class ControlAlgorithm
{
protected:
  Sensor* sensor;
  Drive* drive;
public:
  ControlAlgorithm(Sensor* sens, Drive* drv){
    sensor = sens;
    drive = drv;
  }
  virtual void process(){
  }
};

#endif

