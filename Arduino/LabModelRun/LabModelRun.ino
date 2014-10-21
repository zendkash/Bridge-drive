#include "LabModelSensor.h"
#include "LabModelDrive.h"
#include "PIDControlAlgorithm.h"

LabModelSensor* sensor = new LabModelSensor();
LabModelDrive* drive = new LabModelDrive(sensor, 5.0, 1, 200);
ControlAlgorithm* controller = new PIDControlAlgorithm(sensor, drive, 60, 0, 10, 255);
void setup()
{
  Serial.begin(9600);
  sensor->init();
}

void loop()
{
//  Serial.println("Entering sense");
  sensor->sense();
//  Serial.print(sensor->getfli());
//  Serial.print(", ");
//  Serial.print(sensor->getflo());
//  Serial.print(", ");
//  Serial.print(sensor->getfri());
//  Serial.print(", ");
//  Serial.print(sensor->getfro());
//  Serial.println();
//  Serial.println("Entering process");
  controller->process();
//  Serial.println("Entering driver");
  drive->drive();
}



