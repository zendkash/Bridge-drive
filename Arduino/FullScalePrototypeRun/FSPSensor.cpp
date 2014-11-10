#include "FSPSensor.h"

FSPSensor::FSPSensor() : 
Sensor()
{
  lastfrerr = 0;
  lastflerr = 0;
  
  flerr = 0;
  frerr = 0;
  blerr = 0;
  brerr = 0;
}

void FSPSensor::init()
{
  digitalWrite(FLI_PIN, HIGH);
  digitalWrite(FLO_PIN, HIGH);
  digitalWrite(FRI_PIN, HIGH);
  digitalWrite(FRO_PIN, HIGH);
  
  digitalWrite(BLI_PIN, HIGH);
  digitalWrite(BLO_PIN, HIGH);
  digitalWrite(BRI_PIN, HIGH);
  digitalWrite(BRO_PIN, HIGH);
}

void FSPSensor::sense(bool forward) {
  if(forward) {
  //reset errors if you switch directions
    if(directon != forward){
      lastfrerr = 0;
      lastflerr = 0;
      direction = forward;
    }
    fliraw = digitalRead(FLI_PIN);
    floraw = digitalRead(FLO_PIN);
    friraw = digitalRead(FRI_PIN);
    froraw = digitalRead(FRO_PIN);
  }
  else{
    if(directon != forward){
      lastfrerr = 0;
      lastflerr = 0;
      direction = forward;
    }
    fliraw = digitalRead(BLI_PIN);
    floraw = digitalRead(BLO_PIN);
    friraw = digitalRead(BRI_PIN);
    froraw = digitalRead(BRO_PIN);  
  }

  Serial.print(fliraw);
  Serial.print(", ");
  Serial.print(floraw);
  Serial.print(", ");
  Serial.print(friraw);
  Serial.print(", ");
  Serial.print(froraw);
  Serial.print(", ");

  bool fribool, frobool, flibool, flobool;

  //threshold the raw inputs using flithresh, frithresh, flothresh, frothresh
  fribool = friraw;
  flibool = fliraw;
  frobool = froraw;
  flobool = floraw;
  Serial.print(fribool);
  Serial.print(frobool);
  Serial.print(flibool);
  Serial.print(flobool);
  
  //calculate error based on past state as well (if o was off and i was on before and theyre both off now, make the error far to the o side)
  if(frobool && fribool){
    frerr = 0;
  }
  else if(!frobool){
    if((lastfrerr == 1 || lastfrerr == 2) && !fribool) {
      frerr = 2;
    }
    else if(lastfrerr == -1 || lastfrerr == -2) {
      frerr = -2;
    }
    else {
      frerr = 1;
    }
  }
  else if(!fribool){
    frerr = -1;
  }

  if(flobool && flibool){
    flerr = 0;
  }
  else if(!flibool){
    if((lastflerr == 1 || lastflerr == 2) && !flobool) {
      flerr = 2;
    }
    else if(lastflerr == -1 || lastflerr == -2) {
      flerr = -2;
    }
    else {
      flerr = 1;
    }
  }
  else if(!flobool){
    flerr = -1;
  }

  lastflerr = flerr;
  lastfrerr = frerr;
  //update error values
  brerr = 0;
  blerr = 0;

  
  Serial.print(":");
  Serial.print(frerr);
  Serial.print(":");
  Serial.print(flerr);
  updateEncoder(ENC_L_A_PIN, ENC_L_B_PIN, encLAstate, encLBstate, lenccount);
  updateEncoder(ENC_R_A_PIN, ENC_R_B_PIN, encRAstate, encRBstate, renccount);
}

void FSPSensor::getfrerr(double &tbfrerr) {
  tbfrerr = frerr;
}

void FSPSensor::getflerr(double &tbflerr) {
  tbflerr = flerr;
}

void FSPSensor::getbrerr(double &tbbrerr) {
  tbbrerr = brerr;
}

void FSPSensor::getblerr(double &tbblerr) {
  tbblerr = blerr;
}

void FSPSensor::getlenccount(long &tblenccount) {
  tblenccount = lenccount;
}

void FSPSensor::getrenccount(long &tbrenccount) {
  tbrenccount = renccount;
}

int FSPSensor::getfli() {
  return fliraw;
}

int FSPSensor::getflo() {
  return floraw;
}

int FSPSensor::getfri() {
  return friraw;
}

int FSPSensor::getfro() {
  return froraw;
}



