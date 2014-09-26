#ifndef SIM_BRIDGE_H
#define SIM_BRIDGE_H

#include "..\Sensors\Sensor.h"
#include "..\Drives\Drive.h"


class SimBridge
{
private:
	double x, y, theta; //position information
	double dy, dx, dtheta; //speed information
	Sensor* simsensor; //sensor object to feed values into (this will also exist in the algorithm
	Drive* simdrive; //Drive object that affects the wheels (also exists in algorithtm
public:
    SimBridge();
    void updatePos(int msec);
};

#endif