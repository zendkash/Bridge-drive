#include "SimDrive.h"

SimDrive::SimDrive(SimBridge* simbridge)
{
    bridge = simbridge;
    lspeed = 0;
    rspeed = 0;
}

//void SimDrive::setlspeed(double newlspeed)
//{
//    lspeed = newlspeed;
//}
//void SimDrive::getlspeed(double &tblspeed)
//{
//    tblspeed = lspeed;
//}
//void SimDrive::setrspeed(double newrspeed)
//{
//    rspeed = newrspeed;
//}
//void SimDrive::getrspeed(double &tbrspeed)
//{
//    tbrspeed = rspeed;
//}

void SimDrive::drive()
{
    bridge->setspeeds(lspeed, rspeed);
}