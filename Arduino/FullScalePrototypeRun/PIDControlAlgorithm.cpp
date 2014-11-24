#include "PIDControlAlgorithm.h"
#include <stdio.h>
#include "Arduino.h"

PIDControlAlgorithm::PIDControlAlgorithm(Sensor* inputsensor, Drive* outputdrive, double proportional, double integral, double derivative, double maxspeed) : ControlAlgorithm(inputsensor, outputdrive)
{
    p = proportional;
    i = integral;
    d = derivative;
    maxspd = maxspeed;
    perr = 0;
    ierr = 0;
    derr = 0;
}

void PIDControlAlgorithm::process()
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
    double newperr = p*(flerr + frerr);
    double newierr = ierr + i*(perr);
    double newderr = d*(newperr - perr);
    
//    Serial.print(" ");
//    Serial.print(newperr);
//    Serial.print(" ");
    perr = newperr;
    ierr = newierr;
    derr = newderr;
    
    double totalerr = perr + ierr + derr;
    double nomspeed;
    drive->getnomspd(nomspeed);
//    Serial.print(" ");
//    Serial.print(totalerr);
//    Serial.print(" ");
    totalerr = totalerr*nomspeed/maxspd;
    
//    Serial.print(" ");
//    Serial.print(totalerr);
//    Serial.print(" ");
    drive->setlspd(max(min(nomspeed - totalerr,maxspd),0));
    drive->setrspd(max(min(nomspeed + totalerr,maxspd),0));
}
