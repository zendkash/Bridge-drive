#include "SimBridge.h"
#include <math.h>

SimBridge::SimBridge(double initx,double inity, double inittheta)
{
    x = initx;
    y = inity;
    theta = inittheta;//position information
    lspeed = 0;
    rspeed = 0;//speed information
    width = 12;
    length = 1;
}

//the input time is the timestep to be taken
void SimBridge::updatePos(int msec)
{
    double dl = lspeed*msec/1000;
    double dr = rspeed*msec/1000;
    
    if (abs(dl - dr) < 0.00001)
    {
        x = x - dl * sin(theta);
        y = y + dl * cos(theta);
    }
    else
    {
        double rotradius;
        double rottheta;
        if (dl == 0)
        {
            rotradius = width;
            rottheta = dr / width;
        }
        else
        {
            rotradius = dl*width / (dr - dl);
            rottheta = dl / rotradius;
        }

        double newtheta = theta + rottheta;

        x = x + (rotradius + width / 2) * (cos(newtheta) - cos(theta));
        y = y + (rotradius + width / 2) * (sin(newtheta) - sin(theta));

        theta = newtheta;
    }
    
}


void SimBridge::getpos(double &tbx, double &tby, double &tbtheta)
{
    tbx = x;
    tby = y;
    tbtheta = theta;
}

void SimBridge::getsize(double &tbwidth, double &tblength)
{
    tbwidth = width;
    tblength = length;
}

//Function may have to be modified to have some sort of gradual change in speed rather than a step function changing speed
void SimBridge::setspeeds(double newlspeed, double newrspeed)
{
    lspeed = newlspeed;
    rspeed = newrspeed;
}
