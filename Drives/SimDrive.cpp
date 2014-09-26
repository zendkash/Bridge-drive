#include "SimDrive.h"

SimDrive::SimDrive(SimBridge* simbridge)
{
    bridge = simbridge;
    speed = 0;
}