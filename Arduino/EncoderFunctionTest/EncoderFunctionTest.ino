#define encLAPin 8
#define encLBPin 9
#define encRAPin 10
#define encRBPin 11

boolean encLAstate, encLBstate, encRAstate, encRBstate;
long encAcount = 0;
long encBcount = 0;

void setup() {
  Serial.begin(9600);

  pinMode(encLAPin, INPUT);
  pinMode(encLBPin, INPUT);
  pinMode(encRAPin, INPUT);
  pinMode(encRBPin, INPUT);
  digitalWrite(encLAPin, HIGH);
  digitalWrite(encLBPin, HIGH);
  digitalWrite(encRAPin, HIGH);
  digitalWrite(encRBPin, HIGH);

  encLAstate = digitalRead(encLAPin);
  encLBstate = digitalRead(encLBPin);
  encRAstate = digitalRead(encRAPin);
  encRBstate = digitalRead(encRBPin);
}

void loop() {
  updateEncoder(encLAPin, encLBPin, encLAstate, encLBstate, encAcount);
  updateEncoder(encRAPin, encRBPin, encRAstate, encRBstate, encBcount);
  Serial.print(encAcount); 
  Serial.print(", "); 
  Serial.print(encBcount);
  Serial.println();
}

void updateEncoder(const char aPin, const char bPin, boolean &aState, boolean &bState, long &count) {
  boolean oldAstate = aState;
  boolean oldBstate = bState;
  aState = digitalRead(aPin);
  bState = digitalRead(bPin);
  if((oldAstate != aState) && (oldBstate == bState)) {
    count = count + 1;
  }
  else if((oldAstate == aState) && (oldBstate != bState)) {
    count = count - 1;
  }
  else if((oldAstate != aState) && (oldBstate != bState)) {
    count = 0;
  }
}
