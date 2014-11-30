#include "FSSensor.h"

FSSensor::FSSensor() : 
Sensor()
{
  lastfrerr = 0;
  lastflerr = 0;

  flerr = 0;
  frerr = 0;
  blerr = 0;
  brerr = 0;
}

void FSSensor::init()
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

void FSSensor::sense(bool forward) {
  if(forward) {
    //reset errors if you switch directions
    if(direction != forward){
      lastfrerr = 0;
      lastflerr = 0;

      flerr = 0;
      frerr = 0;
      blerr = 0;
      brerr = 0;
      direction = forward;
    }
    fliraw = digitalRead(FLI_PIN);
    floraw = digitalRead(FLO_PIN);
    friraw = digitalRead(FRI_PIN);
    froraw = digitalRead(FRO_PIN);
    bliraw = digitalRead(BLI_PIN);
    bloraw = digitalRead(BLO_PIN);
    briraw = digitalRead(BRI_PIN);
    broraw = digitalRead(BRO_PIN);
  }
  else{
    if(direction == forward){
      lastfrerr = 0;
      lastflerr = 0;

      flerr = 0;
      frerr = 0;
      blerr = 0;
      brerr = 0;
      direction = !forward;
    }
    fliraw = digitalRead(BRI_PIN);
    floraw = digitalRead(BRO_PIN);
    friraw = digitalRead(BLI_PIN);
    froraw = digitalRead(BLO_PIN);  
    bliraw = digitalRead(FRI_PIN);
    bloraw = digitalRead(FRO_PIN);
    briraw = digitalRead(FLI_PIN);
    broraw = digitalRead(FLO_PIN);
  }

  Serial.print(", FLI: ");
  Serial.print(fliraw);
  Serial.print(", FLO: ");
  Serial.print(floraw);
  Serial.print(", FRI: ");
  Serial.print(friraw);
  Serial.print(", FRO: ");
  Serial.print(froraw);
  Serial.print(", BLI: ");
  Serial.print(bliraw);
  Serial.print(", BLO: ");
  Serial.print(bloraw);
  Serial.print(", BRI: ");
  Serial.print(briraw);
  Serial.print(", BRO: ");
  Serial.print(broraw);

  bool fribool, frobool, flibool, flobool, bribool, brobool, blibool, blobool;

  //threshold the raw inputs using flithresh, frithresh, flothresh, frothresh
  if((fliraw == flirawlast) && (fliraw!=fliboollast)) {
    flibool = fliraw;
  }
  else {
    flibool = fliboollast; 
  }
  if((floraw == florawlast) && (floraw!=floboollast)) {
    flobool = floraw;
  }
  else {
    flobool = floboollast; 
  }
  if((friraw == frirawlast) && (friraw!=friboollast)) {
    fribool = friraw;
  }
  else {
    fribool = friboollast; 
  }
  if((froraw == frorawlast) && (froraw!=froboollast)) {
    frobool = froraw;
  }
  else {
    frobool = froboollast; 
  }
  if((bliraw == blirawlast) && (bliraw!=bliboollast)) {
    blibool = bliraw;
  }
  else {
    blibool = bliboollast; 
  }
  if((bloraw == blorawlast) && (bloraw!=bloboollast)) {
    blobool = bloraw;
  }
  else {
    blobool = bloboollast; 
  }
  if((briraw == brirawlast) && (briraw!=briboollast)) {
    bribool = briraw;
  }
  else {
    bribool = briboollast; 
  }
  if((broraw == brorawlast) && (broraw!=broboollast)) {
    brobool = broraw;
  }
  else {
    brobool = broboollast; 
  }
  //  Serial.print(fribool);
  //  Serial.print(frobool);
  //  Serial.print(flibool);
  //  Serial.print(flobool);

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

  //calculate error based on past state as well (if o was off and i was on before and theyre both off now, make the error far to the o side)
  if(brobool && bribool){
    brerr = 0;
  }
  else if(!brobool){
    if((lastbrerr == 1 || lastbrerr == 2) && !bribool) {
      brerr = 2;
    }
    else if(lastbrerr == -1 || lastbrerr == -2) {
      brerr = -2;
    }
    else {
      brerr = 1;
    }
  }
  else if(!bribool){
    brerr = -1;
  }

  if(blobool && blibool){
    blerr = 0;
  }
  else if(!blibool){
    if((lastblerr == 1 || lastblerr == 2) && !blobool) {
      blerr = 2;
    }
    else if(lastblerr == -1 || lastblerr == -2) {
      blerr = -2;
    }
    else {
      blerr = 1;
    }
  }
  else if(!blobool){
    blerr = -1;
  }

  lastflerr = flerr;
  lastfrerr = frerr;
  //update error values
  lastblerr = blerr;
  lastbrerr = brerr;

  blerr = -blerr;
  brerr = -brerr;

  //  Serial.print(":");
  //  Serial.print(frerr);
  //  Serial.print(":");
  //  Serial.print(flerr);
  fliboollast=flibool;
  floboollast=flobool;
  friboollast=fribool;
  floboollast=frobool;
  bliboollast=blibool;
  bloboollast=blobool;
  briboollast=bribool;
  bloboollast=brobool;

  flirawlast=fliraw;
  florawlast=floraw;
  frirawlast=friraw;
  frorawlast=froraw;
  blirawlast=bliraw;
  blorawlast=bloraw;
  brirawlast=briraw;
  brorawlast=broraw;
}

void FSSensor::getfrerr(double &tbfrerr) {
  tbfrerr = frerr;
}

void FSSensor::getflerr(double &tbflerr) {
  tbflerr = flerr;
}

void FSSensor::getbrerr(double &tbbrerr) {
  tbbrerr = brerr;
}

void FSSensor::getblerr(double &tbblerr) {
  tbblerr = blerr;
}

int FSSensor::getfli() {
  return fliraw;
}

int FSSensor::getflo() {
  return floraw;
}

int FSSensor::getfri() {
  return friraw;
}

int FSSensor::getfro() {
  return froraw;
}

int FSSensor::getbli() {
  return bliraw;
}

int FSSensor::getblo() {
  return bloraw;
}

int FSSensor::getbri() {
  return briraw;
}

int FSSensor::getbro() {
  return broraw;
}

bool FSSensor::allFrontSensorsOff() {
  return (fliraw+friraw+floraw+froraw)==0;
}
bool FSSensor::allBackSensorsOff() {
  return (bliraw+ briraw+bloraw+broraw)==0;
};





