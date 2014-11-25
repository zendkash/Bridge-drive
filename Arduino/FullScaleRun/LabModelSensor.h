#ifndef LAB_MODEL_SENSOR_H
#define LAB_MODEL_SENSOR_H

#include "Sensor.h"
#include "Arduino.h"

#define FLI_ANALOG_PIN 0
#define FLO_ANALOG_PIN 1
#define FRI_ANALOG_PIN 2
#define FRO_ANALOG_PIN 3

#define FLI_PIN A0
#define FLO_PIN A1
#define FRI_PIN A2
#define FRO_PIN A3

#define US_L_TRIG_PIN 2
#define US_L_ECHO_PIN 3
#define US_R_TRIG_PIN 12
#define US_R_ECHO_PIN 13

#define ENC_L_A_PIN 8
#define ENC_L_B_PIN 9
#define ENC_R_A_PIN 10
#define ENC_R_B_PIN 11

#define SPEED_OF_SOUND 58.2
#define MAXIMUM_ULTRASOUND_RANGE 200
#define MINIMUM_ULTRASOUND_RANGE 0

class LabModelSensor: 
public Sensor
{
protected:
  long lenccount;
  long renccount;
  boolean encLAstate;
  boolean encLBstate;
  boolean encRAstate;
  boolean encRBstate;

  double flerr, frerr, blerr, brerr;

  int fliraw;
  int floraw;
  int friraw;
  int froraw;
  double flothresh, frothresh, flithresh, frithresh;
  int lastfrerr, lastflerr;

  double lDistance, rDistance; // Duration used to calculate distance
public:
  LabModelSensor();
  void init();
  void sense();
  double readUltrasonic(const char trigPin, const char echoPin);
  void updateEncoder(const char aPin, const char bPin, boolean &aState, boolean &bState, long &count);
  void getfrerr(double &tbfrerr);
  void getflerr(double &tbflerr);
  void getbrerr(double &tbbrerr);
  void getblerr(double &tbblerr);
  void getlenccount(long &tblenccount);
  void getrenccount(long &tbrenccount);
  int getfli();
  int getflo();
  int getfri();
  int getfro();
};

#endif


