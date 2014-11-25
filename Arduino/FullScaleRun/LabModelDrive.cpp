#include "LabModelDrive.h"

#define EN1 6
#define EN2 5
#define IN1 7
#define IN2 4

void Motor1(int pwm, boolean reverse) {
  if (pwm > 255) {
    pwm = 255;
  }
  if (pwm < 0) {
    pwm = 0;
  }
  analogWrite(EN1,pwm); //set pwm control, 0 for stop, and 255 for maximum speed
  if(reverse) { 
    digitalWrite(IN1,HIGH);    
  }
  else {
    digitalWrite(IN1,LOW);    
  }
}  

void Motor2(int pwm, boolean reverse) {
  if (pwm > 255) {
    pwm = 255;
  }
  if (pwm < 0) {
    pwm = 0;
  }
  analogWrite(EN2,pwm);
  if(reverse) {
    digitalWrite(IN2,HIGH);
  }
  else
  {
    digitalWrite(IN2,LOW);    
  }
}  

LabModelDrive::LabModelDrive(Sensor* newsensor, double wSize, int numcounts, double newnomspd) : 
Drive(newsensor)
{
  wheelSize = wSize;
  countsPerRot = numcounts;
  nomspd = newnomspd;
  analogWrite(EN1, OUTPUT);
  analogWrite(EN2, OUTPUT);
  analogWrite(IN1, OUTPUT);
  analogWrite(IN2, OUTPUT);  
  Motor1(0,false);
  Motor2(0,false);
}

void LabModelDrive::drive()
{
  //Use encoder counts to set the appropriate speed (later, just send the values to the 
  //int lenc, renc;
  //sensor->getlenccount(lenc);
  //sensor->getrenccount(renc);

  Motor1(lspd, true);
  Motor2(rspd, true);

  Serial.print(lspd);
  Serial.print(", ");
  Serial.print(rspd);
  Serial.println();
}

