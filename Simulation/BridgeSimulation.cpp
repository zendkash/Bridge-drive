//includes
#include <stdio.h>
#include "../Abstract Classes/Sensor.h"
#include "../Abstract Classes/Drive.h"
#include "../Abstract Classes/ControlAlgorithm.h"
#include "SimBridge.h"
#include "../Sensors/SimSensor.h"
#include "../Drives/SimDrive.h"
//main code for running the simulation of the bridge drive system

int main( int argv, char** argc )
{
    //setup for the simulation, initializing the physical setup
    //maybe let the inputs be changable values (length, weight of the bridge, length of time to run etc.)
    SimSensor sensors;
    SimDrive drive;
    //SimBridge bridge(sensors, drive, )
    ControlAlgorithm algorithm;
  
    bool exit = false;
    while( !exit )
    {
  
    //run simulation code until exit condition is satisfied
        //sense
        //sensors.sense();
        //process
        //algorithm.process();
        //reflect on the bridge location
        //drive.updateOutput();
        //bridge.updatePosition();

    }

    return;
}