#ifndef SENSOR_H
#define SENSOR_H

class Sensor
{
public:
    virtual void sense(){}
    virtual void getfrerr(double &tbfrerr){};
    virtual void getflerr(double &tbflerr){};
    virtual void getbrerr(double &tbbrerr){};
    virtual void getblerr(double &tbblerr){};
};

#endif