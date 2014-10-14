#ifndef SIM_BRIDGE_H
#define SIM_BRIDGE_H

#include "..\Sensors\Sensor.h"
#include "..\Drives\Drive.h"


class SimBridge
{
private:
	double x, y, theta; //position information
	double lspeed, rspeed; //speed information
    double width, length;
	Sensor* simsensor; //sensor object to feed values into (this will also exist in the algorithm
	Drive* simdrive; //Drive object that affects the wheels (also exists in algorithtm
public:
    SimBridge(double initx = 0, double inity = 0, double inittheta = 0);
    void updatePos(int msec);
    void getpos(double &tbx, double &tby, double &tbtheta);
    void getsize(double &tbwidth, double &tblength);
    void setspeeds(double newlspeed, double newrspeed);
};

#endif