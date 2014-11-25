#ifndef LAB_MODEL_DRIVE_H
#define LAB_MODEL_DRIVE_H
#include "Drive.h"
#include "Sensor.h"
#include "Arduino.h"

class LabModelDrive: 
public Drive
{
protected:
  double wheelSize;
  int countsPerRot;
public:
  LabModelDrive(Sensor* newsensor, double wSize, int numcounts, double newnomspd);
  virtual void drive();
};

#endif

