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
  start=digitalRead(GO_PIN);
  reel=digitalRead(REEL_PIN);
  jog_1=digitalRead(JOG_PIN_1);
  jog_2=digitalRead(JOG_PIN_2);
  main=digitalRead(MAIN_PIN);
}

boolean Remote::getStart() {
  return !start;
}

boolean Remote::getReset() {
  return !reel;
}

boolean Remote::getJog1() {
  return !jog_1; 
}

boolean Remote::getJog2() {
  return !jog_2; 
}

boolean Remote::getMain() {
  return !main;
}



