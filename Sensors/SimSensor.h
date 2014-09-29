#ifndef SIM_SENSOR_H
#define SIM_SENSOR_H


#include "Sensor.h"
#include "../Simulation/SimBridge.h"

class SimSensor : public Sensor
{
private:
    SimBridge* bridge;
    double frerr, flerr, brerr, blerr; //front right error, front left error, back right error, back left error
    double sensorwidth; //the width of the sensor array
    int resolution; //the higher resolution, the more divisions between the edges of the sensor array
                    // 0 is infinite resolution
public:
    SimSensor(SimBridge* simbridge, double width, int res);
    void sense();
    
    void getfrerr(double &tbfrerr);
    void getflerr(double &tbflerr);
    void getbrerr(double &tbbrerr);
    void getblerr(double &tbblerr);
};

#endif