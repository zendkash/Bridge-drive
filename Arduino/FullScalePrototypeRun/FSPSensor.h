#ifndef LAB_MODEL_SENSOR_H
#define LAB_MODEL_SENSOR_H

#include "Sensor.h"
#include "Arduino.h"

#define FLI_PIN 4
#define FLO_PIN 5
#define FRI_PIN A1
#define FRO_PIN A0
#define BLI_PIN A2
#define BLO_PIN A3
#define BRI_PIN 3
#define BRO_PIN 2

class FSPSensor: public Sensor
{
protected:
  bool direction;
  double flerr, frerr, blerr, brerr;

  int fliraw;
  int floraw;
  int friraw;
  int froraw;
  double flothresh, frothresh, flithresh, frithresh;
  int lastfrerr, lastflerr;

  double lDistance, rDistance; // Duration used to calculate distance
public:
  FSPSensor();
  void init();
  void sense(bool forward);
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

