#include "SimSensor.h"
#include <math.h>
#include <algorithm>

using namespace std;
//make sure the sensor resolution is always odd
SimSensor::SimSensor(SimBridge* simbridge, double width=0.1, int res=11)
{
    bridge = simbridge;
    sensorwidth = width;
    resolution = res;
}

void SimSensor::sense()
{
    double x, y, theta;
    bridge->getpos(x, y, theta);
    double width, length;
    bridge->getsize(width, length);
    
    //change in position due to the width
    double dx1 = width / 2 * cos(theta);
    double dy1 = width / 2 * sin(theta);
    //change in position due to the length
    double dx2 = length / 2 * sin(theta);
    double dy2 = length / 2 * cos(theta);

    double frx = x + dx1 - dx2;
    //double fry = y + dy1 + dy2;
    double flx = x - dx1 - dx2;
    //double fly = y - dy1 + dy2;
    double brx = x + dx1 + dx2;
    //double bry = y + dy1 - dy2;
    double blx = x - dx1 + dx2;
    //double bly = y - dy1 - dy2;

    double exfrerr = (frx - width / 2) / cos(theta);
    double exflerr = (flx + width / 2) / cos(theta);
    double exbrerr = (brx - width / 2) / cos(theta);
    double exblerr = (blx + width / 2) / cos(theta);
    
    if (resolution != 0)
    {
        frerr = min(abs(round(exfrerr / (sensorwidth / 2)*resolution)), (double)resolution / 2);
        flerr = min(abs(round(exflerr / (sensorwidth / 2)*resolution)), (double)resolution / 2);
        brerr = min(abs(round(exbrerr / (sensorwidth / 2)*resolution)), (double)resolution / 2);
        blerr = min(abs(round(exblerr / (sensorwidth / 2)*resolution)), (double)resolution / 2);
        if (exfrerr < 0)
            frerr = frerr*-1;
        if (exflerr < 0)
            flerr = flerr*-1;
        if (exbrerr < 0)
            brerr = brerr*-1;
        if (exblerr < 0)
            blerr = blerr*-1;
    }
    else
    {
        frerr = exfrerr;
        flerr = exflerr;
        brerr = exbrerr;
        blerr = exblerr;
    }
    

}

void SimSensor::getfrerr(double &tbfrerr)
{
    tbfrerr = frerr;
}

void SimSensor::getflerr(double &tbflerr)
{
    tbflerr = flerr;
}

void SimSensor::getbrerr(double &tbbrerr)
{
    tbbrerr = brerr;
}

void SimSensor::getblerr(double &tbblerr)
{
    tbblerr = blerr;
}