#include "PIDControlAlgorithm.h"
#include <stdio.h>

PIDControlAlgorithm::PIDControlAlgorithm(Sensor* inputsensor, Drive* outputdrive, double proportional, double integral, double derivative, double speed) : ControlAlgorithm(inputsensor, outputdrive)
{
    p = proportional;
    i = integral;
    d = derivative;
    spd = speed;
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

    double newperr = p*(flerr + frerr);
    double newierr = ierr + i*(perr);
    double newderr = d*(newperr - perr);

    perr = newperr;
    ierr = newierr;
    derr = newderr;

    double totalerr = perr + ierr + derr;

    drive->setlspeed(spd - totalerr);
    drive->setrspeed(spd + totalerr);
}