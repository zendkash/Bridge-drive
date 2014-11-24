#include "FSPSensor.h"
#include "FSPDrive.h"
#include "PIDControlAlgorithm.h"
#include "Arduino.h"
#include <SPI.h>

FSPSensor* sensor = new FSPSensor();

FSPDrive* drive = new FSPDrive(sensor, 0);
//                                                                    P , I,  D
ControlAlgorithm* controller = new PIDControlAlgorithm(sensor, drive, 120, 0, 10, 511); 

void setup()
{
  Serial.begin(9600);
  Serial.flush();
  pinMode(12,INPUT);
  pinMode(7,INPUT);
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  digitalWrite(12, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  sensor->init();
}

void loop()
{
  int spd;
  bool emstop, forward, go, jog;
  spd = analogRead(5)/2;
  emstop = digitalRead(12);
  forward = digitalRead(7);
  go = digitalRead(8);
  jog = digitalRead(9);
  //since the emergency stop is normally open, switch convension to make logical sense
  emstop = !emstop;
  
  Serial.print("EM Stop: ");
  Serial.print(emstop);
  Serial.print(", Forward: ");
  Serial.print(forward);
  Serial.print(", Go: ");
  Serial.print(go);
  Serial.print(", Jog: ");
  Serial.print(jog);
  Serial.print(", Speed: ");
  Serial.print(spd);
  
  if (!emstop){
    if(go){
    //  Serial.println("Entering sense");
      sensor->sense(forward);
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
      drive->drive(spd,forward);
    }
    else if(jog){
      drive->setlspd(spd);
      drive->setrspd(spd);
      drive->drive(spd, forward);
    }
    else{
      drive->setlspd(0);
      drive->setrspd(0);
      drive->drive(spd, forward);
    }
  }
  else{
    drive->setlspd(0);
    drive->setrspd(0);
    drive->drive(spd, forward);
  }  
  Serial.print(", Time: ");
  Serial.println(millis());
}
