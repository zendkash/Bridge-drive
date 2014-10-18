#include "LabModelSensor.h"

LabModelSensor::LabModelSensor() : Sensor()
{
  
  flothresh = 600;
  frothresh = 550;
  flithresh = 700;
  frithresh = 600;
  lastfrerr = 0;
  lastflerr = 0;
}

void LabModelSensor::init()
{
  digitalWrite(FLI_PIN, HIGH);
  digitalWrite(FLO_PIN, HIGH);
  digitalWrite(FRI_PIN, HIGH);
  digitalWrite(FRO_PIN, HIGH);

  pinMode(US_R_TRIG_PIN, OUTPUT);
  pinMode(US_R_ECHO_PIN, INPUT);
  pinMode(US_L_TRIG_PIN, OUTPUT);
  pinMode(US_L_ECHO_PIN, INPUT);

  pinMode(ENC_L_A_PIN, INPUT);
  pinMode(ENC_L_B_PIN, INPUT);
  pinMode(ENC_R_A_PIN, INPUT);
  pinMode(ENC_R_B_PIN, INPUT);

  digitalWrite(ENC_L_A_PIN, HIGH);
  digitalWrite(ENC_L_B_PIN, HIGH);
  digitalWrite(ENC_R_A_PIN, HIGH);
  digitalWrite(ENC_R_B_PIN, HIGH);
}

void LabModelSensor::sense() {
  lDistance=readUltrasonic(US_L_TRIG_PIN, US_L_ECHO_PIN);
  rDistance=readUltrasonic(US_R_TRIG_PIN, US_R_ECHO_PIN);
  fliraw = analogRead(FLI_ANALOG_PIN);
  floraw = analogRead(FLO_ANALOG_PIN);
  friraw = analogRead(FRI_ANALOG_PIN);
  froraw = analogRead(FRO_ANALOG_PIN);
  
  bool fribool, frobool, flibool, flobool;
  
  //threshold the raw inputs using flithresh, frithresh, flothresh, frothresh
  fribool = friraw > frithresh;
  flibool = fliraw > flithresh;
  frobool = froraw > frothresh;
  flobool = floraw > flothresh;
  
  //calculate error based on past state as well (if o was off and i was on before and theyre both off now, make the error far to the o side)
  if(frobool && fribool){
    frerr = 0;
  }
  else if(!frobool){
    if(lastfrerr == 1 && !flibool) {frerr = 2;}
    else if(lastfrerr == -1) {frerr = -2;}
    else {frerr = 1;}
  }
  else if(!fribool){
    frerr = -1;
  }
  
  if(flobool && flibool){
    flerr = 0;
  }
  else if(!flibool){
    if(lastflerr == 1 && !flobool) {frerr = 2;}
    else if(lastflerr == -1) {frerr = -2;}
    else {flerr = 1;}
  }
  else if(!flobool){
    flerr = -1;
  }
  
  lastflerr = flerr;
  lastfrerr = frerr;
  //update error values
  brerr = 0;
  blerr = 0;

  updateEncoder(ENC_L_A_PIN, ENC_L_B_PIN, encLAstate, encLBstate, lenccount);
  updateEncoder(ENC_R_A_PIN, ENC_R_B_PIN, encRAstate, encRBstate, renccount);
}

double LabModelSensor::readUltrasonic(const char trigPin, const char echoPin) {
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);

  //Calculate the distance (in cm) based on the speed of sound.
  return pulseIn(echoPin, HIGH)/SPEED_OF_SOUND;
}

void LabModelSensor::updateEncoder(const char aPin, const char bPin, boolean &aState, boolean &bState, long &count) {
  boolean oldAstate = aState;
  boolean oldBstate = bState;
  aState = digitalRead(aPin);
  bState = digitalRead(bPin);
  if((oldAstate != aState) || (oldBstate != bState)) { //this isn't implemented properly but I'll make this better later
    count = count + 1;
  } 
}

void LabModelSensor::getfrerr(double &tbfrerr) {
  tbfrerr = frerr;
}

void LabModelSensor::getflerr(double &tbflerr) {
  tbflerr = flerr;
}

void LabModelSensor::getbrerr(double &tbbrerr) {
  tbbrerr = brerr;
}

void LabModelSensor::getblerr(double &tbblerr) {
  tbblerr = blerr;
}

void LabModelSensor::getlenccount(long &tblenccount) {
  tblenccount = lenccount;
}

void LabModelSensor::getrenccount(long &tbrenccount) {
  tbrenccount = renccount;
}

int LabModelSensor::getfli() {
  return fliraw;
}

int LabModelSensor::getflo() {
  return floraw;
}

int LabModelSensor::getfri() {
  return friraw;
}

int LabModelSensor::getfro() {
  return froraw;
}

