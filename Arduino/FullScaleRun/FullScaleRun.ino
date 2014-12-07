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

#define JOGSPEED 700

#define MAX_NOSENSE_ITERATIONS 5

FSSensor* sensor = new FSSensor();

FSDrive* drive = new FSDrive(sensor, 0);
//                                                                    P , I,  D, w, F, R
ControlAlgorithm* controller = new PIDControlAlgorithm(sensor, drive, 100, 0, 0, 0, 1, 0.75, 0, 1023); 
Remote* remote = new Remote();

int spd;
bool forward, reverse, jog;
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
  sensor->sense(forward);
  //since the emergency stop is normally open, switch convension to make logical sense

  //  Serial.print("Switches: {FWD ");
  //  Serial.print(forward);
  //  Serial.print(", REV ");
  //  Serial.print(reverse);
  //  Serial.print(", JOG ");
  //  Serial.print(jog);
  //  Serial.print(", SPD ");
  //  Serial.print(spd);
  Serial.print("} Remote: {GO ");
  Serial.print(remote->getStart());
  //  Serial.print(", JOGA");
  //  Serial.print(remote->getJogAll());
  //  Serial.print(", JOG1");
  //  Serial.print(remote->getJog1());
  //  Serial.print(", JOG2 ");
  //  Serial.print(remote->getJog2());
  //  Serial.print("}");
  if(remote->getStart()){
    if(jog||remote->getJogAll()){
      drive->setlspd(JOGSPEED);
      drive->setrspd(JOGSPEED);
      drive->drive(JOGSPEED, forward);
    }
    else if(remote->getJog1()){
      drive->setlspd(JOGSPEED);
      drive->setrspd(0);
      drive->drive(spd, forward);
    }
    else if(remote->getJog2()){
      drive->setlspd(0);
      drive->setrspd(JOGSPEED);
      drive->drive(spd, forward);
    }
    else if((numIterationsOffTrack < MAX_NOSENSE_ITERATIONS) && (forward || reverse)){
      controller->process(forward);
      //  Serial.println("Entering driver");
      drive->drive(spd,forward);
    }
    else{
      drive->setlspd(0);
      drive->setrspd(0);
      drive->drive(spd, forward);
    }
  }
  else {
    if(jog||remote->getJogAll()){
      drive->setlspd(spd);
      drive->setrspd(spd);
      drive->drive(spd, forward);
    }
    else if(remote->getJog1()){
      drive->setlspd(spd);
      drive->setrspd(0);
      drive->drive(spd, forward);
    }
    else if(remote->getJog2()){
      drive->setlspd(0);
      drive->setrspd(spd);
      drive->drive(spd, forward);
    }
    else {
      drive->setlspd(0);
      drive->setrspd(0);
      drive->drive(spd, forward);
    }
  }

  if(remote->getReset()) {
    numIterationsOffTrack=0;
  }
  else if(numIterationsOffTrack < MAX_NOSENSE_ITERATIONS) {
    if(sensor->allFrontSensorsOff()) {
      numIterationsOffTrack+=1;
    }
    else {
      numIterationsOffTrack=0;
    }
  }
  Serial.print(", Time: ");
  Serial.println(millis());
}






