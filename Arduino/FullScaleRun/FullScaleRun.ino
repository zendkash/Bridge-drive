#include "FSSensor.h"
#include "FSDrive.h"
#include "PIDControlAlgorithm.h"
#include "Arduino.h"
#include "Remote.h"
#include <SPI.h>

#define FORWARDSWITCH 43
#define REVERSESWITCH 44
#define JOGSWITCH 45
#define SPEEDPOT 0

#define MAX_NOSENSE_ITERATIONS 3

FSSensor* sensor = new FSSensor();

FSDrive* drive = new FSDrive(sensor, 0);
//                                                                    P , I,  D,  w
ControlAlgorithm* controller = new PIDControlAlgorithm(sensor, drive, 120, 0, 10, 0.5, 1023); 
Remote* remote = new Remote();

int spd;
bool forward, reverse, jog;
bool forwarddirection;
int numIterationsOffTrack;

void setup()
{
  Serial.begin(9600);
  Serial.flush();
  pinMode(FORWARDSWITCH,INPUT);
  pinMode(REVERSESWITCH,INPUT);
  pinMode(JOGSWITCH,INPUT);
  digitalWrite(FORWARDSWITCH,HIGH);
  digitalWrite(REVERSESWITCH,HIGH);
  digitalWrite(JOGSWITCH,HIGH);
  sensor->init();
  remote->init();
}

void loop()
{
  spd = analogRead(SPEEDPOT);
  forward = !digitalRead(FORWARDSWITCH);
  reverse = !digitalRead(REVERSESWITCH);
  jog = digitalRead(JOGSWITCH);
  remote->check();
  //since the emergency stop is normally open, switch convension to make logical sense

  Serial.print("Switches: {FWD ");
  Serial.print(forward);
  Serial.print(", REV ");
  Serial.print(reverse);
  Serial.print(", JOG ");
  Serial.print(jog);
  Serial.print(", SPD ");
  Serial.print(spd);
  Serial.print("} Remote: {GO ");
  Serial.print(remote->getStart());
  Serial.print(", RST ");
  Serial.print(remote->getReset());
  Serial.print(", JOG ");
  Serial.print(remote->getJog1());
  Serial.print(", EXT ");
  Serial.print(remote->getJog2());
  Serial.print("}");

  if(numIterationsOffTrack < MAX_NOSENSE_ITERATIONS) {
    if(remote->getStart() && (forward || reverse)){
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
    else if(jog || remote->getJog1()){
      drive->setlspd(spd);
      drive->setrspd(spd);
      drive->drive(spd, forward);
    }
    else{
      drive->setlspd(0);
      drive->setrspd(0);
      drive->drive(spd, forward);
    }
    if(sensor->allFrontSensorsOff() || sensor->allBackSensorsOff()) {
      numIterationsOffTrack+=1;
    }
  }
  else {
    drive->setlspd(0);
    drive->setrspd(0);
    drive->drive(spd, forward);
  }
  if(remote->getReset()) {
    numIterationsOffTrack=0;
  }
  Serial.print(", Time: ");
  Serial.println(millis());
}









