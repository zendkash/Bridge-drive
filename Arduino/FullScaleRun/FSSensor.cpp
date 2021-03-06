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
  fricount=0;
  frocount=0;
  flicount=0;
  flocount=0;
  bricount=0;
  brocount=0;
  blicount=0;
  blocount=0;

  lastfrerr = 0;
  lastflerr = 0;
  lastbrerr = 0;
  lastblerr = 0;
}

void FSSensor::sense(bool forward) {
  if(forward) {
    //reset errors if you switch directions
    if(direction != forward){
      lastfrerr = 0;
      lastflerr = 0;
      lastbrerr = 0;
      lastblerr = 0;

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
    if(direction != forward){
      lastfrerr = 0;
      lastflerr = 0;
      lastbrerr = 0;
      lastblerr = 0;

      flerr = 0;
      frerr = 0;
      blerr = 0;
      brerr = 0;
      direction = forward;
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

  bool fribool, frobool, flibool, flobool, bribool, brobool, blibool, blobool;

  //threshold the raw inputs using flithresh, frithresh, flothresh, frothresh
  if((fliraw == flirawlast) && (fliraw!=fliboollast)) {
    flicount = flicount+1;
    if(flicount > MAXCOUNT){
      flibool = fliraw;
    }
    else{
      flibool = fliboollast;
    }
  }
  else {
    flibool = fliboollast; 
    flicount = 0;
  }
  if((floraw == florawlast) && (floraw!=floboollast)) {
    flocount = flocount+1;
    if(flocount > MAXCOUNT){
      flobool = floraw;
    }
    else{
      flobool = floboollast;
    }
  }
    else {
    flobool = floboollast; 
    flocount = 0;
  }
  if((friraw == frirawlast) && (friraw!=friboollast)) {
    fricount = fricount+1;
    if(fricount > MAXCOUNT){
      fribool = friraw;
    }
    else{
      fribool = friboollast;
    }
  }
  else {
    fribool = friboollast; 
    fricount = 0;
  }
  if((froraw == frorawlast) && (froraw!=froboollast)) {
    frocount = frocount+1;
    if(frocount > MAXCOUNT){
      frobool = froraw;
    }
    else{
      frobool = froboollast;
    }
  }
  else {
    frobool = froboollast; 
    frocount = 0;
  }
  if((bliraw == blirawlast) && (bliraw!=bliboollast)) {
    blicount = blicount + 1;
    if(blicount > MAXCOUNT){
      blibool = bliraw;
    }
    else{
      blibool = bliboollast;
    }
  }
  else {
    blibool = bliboollast; 
    blicount = 0;
  }
  if((bloraw == blorawlast) && (bloraw!=bloboollast)) {
    blocount = blocount+1;
    if(blocount > MAXCOUNT){
      blobool = bloraw;
    }
    else{
      blobool = bloboollast;
    }
  }
  else {
    blobool = bloboollast; 
    blocount = 0;
  }
  if((briraw == brirawlast) && (briraw!=briboollast)) {
    bricount = bricount + 1;
    if(bricount > MAXCOUNT){
      bribool = briraw;
    }
    else{
      bribool = briboollast;
    }
  }
  else {
    bribool = briboollast; 
    bricount = 0;
  }
  if((broraw == brorawlast) && (broraw!=broboollast)) {
    brocount = brocount + 1;
    if(brocount > MAXCOUNT){
      brobool = broraw;
    }
    else{
      brobool = broboollast;
    }
  }
  else {
    brobool = broboollast; 
    brocount = 0;
  }
  //  Serial.print(fribool);
  //  Serial.print(frobool);p
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
  froboollast=frobool;
  bliboollast=blibool;
  bloboollast=blobool;
  briboollast=bribool;
  broboollast=brobool;

  flirawlast=fliraw;
  florawlast=floraw;
  frirawlast=friraw;
  frorawlast=froraw;
  blirawlast=bliraw;
  blorawlast=bloraw;
  brirawlast=briraw;
  brorawlast=broraw;

  Serial.print(", FLI: ");
  Serial.print(fliraw);
  Serial.print(flibool);
  Serial.print(", FLO: ");
  Serial.print(floraw);
  Serial.print(flobool);
  Serial.print(", FRI: ");
  Serial.print(friraw);
  Serial.print(fribool);
  Serial.print(", FRO: ");
  Serial.print(froraw);
  Serial.print(frobool);
  Serial.print(", BLI: ");
  Serial.print(bliraw);
  Serial.print(blibool);
  Serial.print(", BLO: ");
  Serial.print(bloraw);
  Serial.print(blobool);  
  Serial.print(", BRI: ");
  Serial.print(briraw);
  Serial.print(bribool);
  Serial.print(", BRO: ");
  Serial.print(broraw);
  Serial.print(brobool);

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
  return fliboollast;
}

int FSSensor::getflo() {
  return floboollast;
}

int FSSensor::getfri() {
  return friboollast;
}

int FSSensor::getfro() {
  return froboollast;
}

int FSSensor::getbli() {
  return bliboollast;
}

int FSSensor::getblo() {
  return bloboollast;
}

int FSSensor::getbri() {
  return briboollast;
}

int FSSensor::getbro() {
  return broboollast;
}

bool FSSensor::allFrontSensorsOff() {
  return (fliraw+friraw+floraw+froraw)==0;
}
bool FSSensor::allBackSensorsOff() {
  return (bliraw+briraw+bloraw+broraw)==0;
};
