#ifndef LAB_MODEL_DRIVE_H
#define LAB_MODEL_DRIVE_H
#include "Drive.h"
#include "Sensor.h"
#include "Arduino.h"
#include <SPI.h>

class FSDrive: 
public Drive
{
protected:
public:
  FSDrive(Sensor* newsensor, double newnomspd);
  virtual void drive(int nomspeed, bool forward);
};

#endif

