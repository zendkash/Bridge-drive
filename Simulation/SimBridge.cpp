#include "SimBridge.h"

SimBridge::SimBridge()
{
    x = 0;
    y = 0;
    theta = 0;//position information
    dy = 0;
    dx = 0;
    dtheta = 0;//speed information
}

//the input time is the timestep to be taken
void SimBridge::updatePos(int msec)
{

}