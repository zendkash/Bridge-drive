#include "SimBridge.h"
#include <math.h>

SimBridge::SimBridge()
{
    x = 0;
    y = 0;
    theta = 0;//position information
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
    
    double rotradius = dl*width/(dr-dl);
    double rottheta = dl/rotradius;
    
    double thetanew = theta+rottheta;
    
    x = x + ( rotradius + width / 2 ) * ( cos(thetanew) - cos(theta) );
    y = y + ( rotradius + width / 2 ) * ( sin(thetanew) - sin(theta) );
    
    theta = newtheta;
}


void getpos(double &tbx, double &tby, double &tbtheta)
{
    tbx = x;
    tby = y;
    tbtheta = theta;
}

void getsize(double &tbwidth, double &tblength)
{
    tbwidth = width;
    tblength = length;
}

//Function may have to be modified to have some sort of gradual change in speed rather than a step function changing speed
void setspeeds(double newlspeed, double newrspeed)
{
    lspeed = newlspeed;
    rspeed = newrspeed;
}
