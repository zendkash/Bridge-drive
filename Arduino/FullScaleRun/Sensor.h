#ifndef SENSOR_H
#define SENSOR_H

class Sensor
{
public:
  virtual void init(){
  };
  virtual void sense(){
  };
  virtual void getfrerr(double &tbfrerr){
  };
  virtual void getflerr(double &tbflerr){
  };
  virtual void getbrerr(double &tbbrerr){
  };
  virtual void getblerr(double &tbblerr){
  };
  virtual void getlenccount(int &tblenccount){
  };
  virtual void getrenccount(int &tbrenccount){
  };
};

#endif

