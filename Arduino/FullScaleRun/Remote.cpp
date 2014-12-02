#include "Remote.h"
#include "Arduino.h"

Remote::Remote() {
}

void Remote::init() {
  pinMode(GO_PIN,INPUT);
  pinMode(REEL_PIN,INPUT);
  pinMode(JOG_PIN_1,INPUT);
  pinMode(JOG_PIN_2,INPUT);
  pinMode(MAIN_PIN,INPUT);
  digitalWrite(GO_PIN,HIGH);
  digitalWrite(REEL_PIN,HIGH);
  digitalWrite(JOG_PIN_1,HIGH);
  digitalWrite(JOG_PIN_2,HIGH);
  digitalWrite(MAIN_PIN,HIGH);
}

void Remote::check() {
  boolean startraw, reelraw, jog_1raw, jog_2raw, mainraw;
  startraw=digitalRead(GO_PIN);
  reelraw=digitalRead(REEL_PIN);
  jog_1raw=digitalRead(JOG_PIN_1);
  jog_2raw=digitalRead(JOG_PIN_2);
  mainraw=digitalRead(MAIN_PIN);
  if((startraw == startrawlast) && (startraw!=startlast)) {
    start = startraw;
  }
  else {
    start = startlast; 
  }
  if((reelraw == reelrawlast) && (reelraw!=reellast)) {
    reel = reelraw;
  }
  else {
    reel = reellast; 
  }
  if((jog_1raw == jog_1rawlast) && (jog_1raw!=jog_1last)) {
    jog_1 = jog_1raw;
  }
  else {
    jog_1 = jog_1last; 
  }
  if((jog_2raw == jog_2rawlast) && (jog_2raw!=jog_2last)) {
    jog_2 = jog_2raw;
  }
  else {
    jog_2 = jog_2last; 
  }
  if((mainraw == mainrawlast) && (mainraw!=mainlast)) {
    main = mainraw;
  }
  else {
    main = mainlast; 
  }
  startrawlast = startraw;
  reelrawlast = reelraw;
  jog_1rawlast = jog_1raw;
  jog_2rawlast = jog_2raw;
  mainrawlast = mainraw;

  startlast = start;
  reellast = reel;
  jog_1last = jog_1;
  jog_2last = jog_2;
  mainlast = main;
}

boolean Remote::getStart() {
  return !start;
}

boolean Remote::getReset() {
  return start;
}

boolean Remote::getJog1() {
  return !jog_1;
}

boolean Remote::getJog2() {
  return !jog_2; 
}

boolean Remote::getJogAll() {
  return !reel;
}

boolean Remote::getMain() {
  return !main;
}






