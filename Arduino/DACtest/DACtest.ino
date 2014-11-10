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
    writetoDAC(1, serialData);
//    writetoDAC(1, serialData);
//    writetoDAC(2, serialData);
    writetoDAC(2, serialData);
    Serial.flush();
  }
}

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

