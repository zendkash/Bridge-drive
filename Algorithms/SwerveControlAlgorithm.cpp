#include "SwerveControlAlgorithm.h"
#include <math.h>

#define PI 3.14159265359

SwerveControlAlgorithm::SwerveControlAlgorithm(Sensor* sens, Drive* drv, double speed) :ControlAlgorithm(sens, drv)
{
    count = 0;
    swerve = false;
    maxspeed = speed;
}

void SwerveControlAlgorithm::process()
{
    drive->setlspeed(-0.1*cos(count * 2 * PI / 100) + 0.1);
    if (swerve == false && (0.1*cos(count * 2 * PI / 100) + 0.1) > -0.1*cos(count * 2 * PI / 100) + 0.1)
    {
        drive->setrspeed(-0.1*cos(count * 2 * PI / 100) + 0.1);
    }
    else
    {
        swerve = true;
        drive->setrspeed(0.1*cos(count * 2 * PI / 100) + 0.1);
    }

    count++;
    if (count > 100)
    {
        count = 1;
    }
}