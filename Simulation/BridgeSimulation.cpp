//includes
#include <stdio.h>
#include "../Sensors/Sensor.h"
#include "../Drives/Drive.h"
#include "../Algorithms/ControlAlgorithm.h"
#include "../Algorithms/SwerveControlAlgorithm.h"
#include "../Algorithms/PIDControlAlgorithm.h"
#include "SimBridge.h"
#include "../Sensors/SimSensor.h"
#include "../Drives/SimDrive.h"
//main code for running the simulation of the bridge drive system

int main( int argv, char** argc )
{
    //setup for the simulation, initializing the physical setup
    //maybe let the inputs be changable values (length, weight of the bridge, length of time to run etc.)
    SimBridge* bridge = new SimBridge(0,0,0.25);
    SimSensor* sensors = new SimSensor(bridge, 0.02, 2);
    SimDrive* drive = new SimDrive(bridge);
    PIDControlAlgorithm algorithm(sensors, drive, 1, 0, 1, 0.2);
    int count = 0;
    bool exit = false;
    double x, y, theta;
    FILE *outfile;
    fopen_s(&outfile, "run.dat", "w");

    while( count < 1000 )
    {
  
    //run simulation code until exit condition is satisfied
        //sense
        sensors->sense();
        //process
        algorithm.process();
        //reflect on the bridge location
        drive->drive();
        bridge->updatePos(100);
        bridge->getpos(x, y, theta);
        printf("%f\t%f\t%f\n", x, y, theta);
        fprintf(outfile, "%f\t%f\t%f\n", x, y, theta);
        count++;
    }
    fclose(outfile);
    getchar();
    return 0;
}