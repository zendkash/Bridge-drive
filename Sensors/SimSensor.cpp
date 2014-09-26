#include "SimSensor.h"

SimSensor::SimSensor(SimBridge* simbridge, double width, int res)
{
    bridge = simbridge;
    sensorwidth = width;
    resolution = res;
}