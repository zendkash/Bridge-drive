#include "FSPDrive.h"
#include <Arduino.h>
#include <SPI.h>
#define EN1 6
#define EN2 5
#define IN1 7
#define IN2 4
#define SLAVEPIN 10

int writetoDAC(int operation, int value){
  int r1, r0;
  switch (operation){
  case 0:
    r0 = 0;
    r1 = 0;
    break;
  case 1:
    r0 = 4096;
    r1 = 0;    
    break;
  case 2:
    r0 = 0;
    r1 = 32768;
    break;
  default:
    return -1;
  }
  int data = r0 + r1 + (value<<2);
//  for(int i = 15; i != -1; i--) {
//    Serial.print(0x01&(data>>i));
//  }
//  Serial.println();

  int secondbyte = data;
  int firstbyte = data >> 8;
  digitalWrite(SLAVEPIN,LOW);
  SPI.transfer(firstbyte);
  SPI.transfer(secondbyte);
  digitalWrite(SLAVEPIN,HIGH);
}

void Motor1(int val) {
  writetoDAC(1, val);
}  

void Motor2(int val) {
  writetoDAC(2, val);
}  

FSPDrive::FSPDrive(Sensor* newsensor, double newnomspd) : 
Drive(newsensor)
{
  nomspd = newnomspd;
  // set the slaveSelectPin as an output:
  pinMode (SLAVEPIN, OUTPUT);
  // initialize SPI:
  SPI.begin(); 
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.setDataMode(SPI_MODE2);
  Motor1(0);
  Motor2(0);
}

void FSPDrive::drive(int nomspeed, bool forward)
{
  nomspd = nomspeed;
  //Use encoder counts to set the appropriate speed (later, just send the values to the 
  //int lenc, renc;
  //sensor->getlenccount(lenc);
  //sensor->getrenccount(renc);
  if (forward){
    Motor1(lspd);
    Motor2(rspd);  
  }
  else {
    Motor1(rspd);
    Motor2(lspd);  
  }
  
  Serial.print(", lspd: ");
  Serial.print(lspd);
  Serial.print(", rspd: ");
  Serial.print(rspd);
}
