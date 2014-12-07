#include "PIDControlAlgorithm.h"
#include <stdio.h>
#include "Arduino.h"

PIDControlAlgorithm::PIDControlAlgorithm(Sensor* inputsensor, Drive* outputdrive, double proportional, double integral, double derivative, double weight, double frontscale, double rearscale, double minspeed, double maxspeed) : 
ControlAlgorithm(inputsensor, outputdrive)
{
  p = proportional;
  i = integral;
  d = derivative;
  w = weight;
  minspd = minspeed;
  maxspd = maxspeed;
  perr = 0;
  ierr = 0;
  derr = 0;
  frontscl = frontscale;
  rearscl = rearscale;
}

void PIDControlAlgorithm::process(bool direction)
{
  double flerr, frerr, blerr, brerr;
  sensor->getflerr(flerr);
  sensor->getblerr(blerr);
  sensor->getfrerr(frerr);
  sensor->getbrerr(brerr);
  //printf("%f\t%f\n", flerr, frerr);
  //getchar();
  //    Serial.print(" ");
  //    Serial.print(flerr);
  //    Serial.print(" ");
  //    Serial.print(" ");
  //    Serial.print(frerr);
  //    Serial.print(" ");
  double newperr = p*(flerr + frerr + w*(blerr + brerr))/(1+w);
  double newierr = ierr + i*(perr);
  double newderr = d*(newperr - perr);

  //    Serial.print(" ");
  //    Serial.print(newperr);
  //    Serial.print(" ");
  perr = newperr;
  ierr = newierr;
  derr = newderr;

  double totalerr;
  if(direction==FORWARD) {
    totalerr = frontscl*(perr + ierr + derr);
  }
  else {
    totalerr = rearscl*(perr + ierr + derr);
  }
  double nomspeed;
  drive->getnomspd(nomspeed);
  //    Serial.print(" ");
  //    Serial.print(totalerr);
  //    Serial.print(" ");

  //totalerr = totalerr*nomspeed/maxspd;

  //    Serial.print(" ");
  //    Serial.print(totalerr);
  //    Serial.print(" ");
  drive->setlspd(max(min(nomspeed - 2*totalerr,maxspd),nomspeed));
  drive->setrspd(max(min(nomspeed + 2*totalerr,maxspd),nomspeed));
}


