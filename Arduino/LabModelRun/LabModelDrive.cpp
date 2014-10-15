#include "LabModelDrive.h"

LabModelDrive::LabModelDrive(Sensor* newsensor, double wSize, int numcounts) : Drive(newsensor)
{
    wheelSize = wSize;
    countsPerRot = numcounts;
}

void LabModelDrive::drive()
{
  //Use encoder counts to set the appropriate speed
  int lenc, renc;
  sensor->getlenccount(lenc);
  sensor->getrenccount(renc);
}
