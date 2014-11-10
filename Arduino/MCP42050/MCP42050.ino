#include <SPI.h>

// set pin 10 as the slave select for the digital pot:
const int slavepin = 10;
int serialData;

void setup() {
  // set the slaveSelectPin as an output:
  pinMode (slavepin, OUTPUT);
  // initialize SPI:
  SPI.begin(); 
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV2);
  SPI.setDataMode(SPI_MODE2);
  Serial.begin(9600);
}

void loop(){
  if(Serial.available()) {
    serialData = Serial.parseInt();
    //    Serial.print("Received ");
    //    Serial.println(serialData);
    writetoPot(2, serialData);
    Serial.flush();
  }
}

int writetoPot(int channel, int value){
  int p1, p0;
  switch (channel){
  case 0:
    p0 = 256;
    p1 = 0;
    break;
  case 1:
    p0 = 0;
    p1 = 512;    
    break;
  case 2:
    p0 = 256;
    p1 = 512;
    break;
  default:
    return -1;
  }
  int data = p0 + p1 + value + 4096;
  for(int i = 15; i != -1; i--) {
    Serial.print(0x01&(data>>i));
  }
  Serial.println();

  int secondbyte = data;
  int firstbyte = data >> 8;
  digitalWrite(slavepin,LOW);
  SPI.transfer(firstbyte);
  SPI.transfer(secondbyte);
  digitalWrite(slavepin,HIGH);
}

