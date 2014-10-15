#define fliPin 0
#define floPin 1
#define friPin 2
#define froPin 3

#define usrTrigPin 12
#define usrEchoPin 13
#define uslTrigPin 2
#define uslEchoPin 3

#define encLAPin 8
#define encLBPin 9
#define encRAPin 10
#define encRBPin 11

int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long lDuration, lDistance, rDuration, rDistance; // Duration used to calculate distance

int fli, flo, fri, fro;
boolean encLA, encLB, encRA, encRB;
unsigned long time;

void setup()
{
  Serial.begin(9600);

  //  pinMode(fliPin, INPUT);
  //  pinMode(floPin, INPUT);
  //  pinMode(friPin, INPUT);
  //  pinMode(froPin, INPUT);
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);

  pinMode(usrTrigPin, OUTPUT);
  pinMode(usrEchoPin, INPUT);
  pinMode(uslTrigPin, OUTPUT);
  pinMode(uslEchoPin, INPUT);

  pinMode(encLAPin, INPUT);
  pinMode(encLBPin, INPUT);
  pinMode(encRAPin, INPUT);
  pinMode(encRBPin, INPUT);
  digitalWrite(encLAPin, HIGH);
  digitalWrite(encLBPin, HIGH);
  digitalWrite(encRAPin, HIGH);
  digitalWrite(encRBPin, HIGH);
}

void loop()
{
  time=micros();
//  //USL
//  /* The following trigPin/echoPin cycle is used to determine the
//   distance of the nearest object by bouncing soundwaves off of it. */
//  digitalWrite(uslTrigPin, LOW); 
//  delayMicroseconds(2); 
//
//  digitalWrite(uslTrigPin, HIGH);
//  delayMicroseconds(10); 
//
//  digitalWrite(uslTrigPin, LOW);
//  lDuration = pulseIn(uslEchoPin, HIGH);
//
//  //Calculate the distance (in cm) based on the speed of sound.
//  lDistance = lDuration/58.2;
//
//  //USR
//  /* The following trigPin/echoPin cycle is used to determine the
//   distance of the nearest object by bouncing soundwaves off of it. */
//  digitalWrite(usrTrigPin, LOW); 
//  delayMicroseconds(2); 
//
//  digitalWrite(usrTrigPin, HIGH);
//  delayMicroseconds(10); 
//
//  digitalWrite(usrTrigPin, LOW);
//  rDuration = pulseIn(usrEchoPin, HIGH);
//
//  //Calculate the distance (in cm) based on the speed of sound.
//  rDistance = rDuration/58.2;

  //Read QRDs
  fli = analogRead(fliPin);
  flo = analogRead(floPin);
  fri = analogRead(friPin);
  fro = analogRead(froPin);

  //Read encoders
//  encLA = digitalRead(encLAPin);
//  encLB = digitalRead(encLBPin);
//  encRA = digitalRead(encRAPin);
//  encRB = digitalRead(encRBPin);
  
  Serial.print(micros()-time);
  Serial.println();
  
  Serial.print(fli); 
  Serial.print(' ');
  Serial.print(flo); 
  Serial.print(' ');
  Serial.print(fri); 
  Serial.print(' ');
  Serial.print(fro);
  Serial.println();

  Serial.print(encLA); 
  Serial.print(' ');
  Serial.print(encLB); 
  Serial.print(' ');
  Serial.print(encRA); 
  Serial.print(' ');
  Serial.print(encRB);
  Serial.println();

  Serial.print(lDistance); 
  Serial.print(' ');
  Serial.print(rDistance);
  Serial.println();
  Serial.println();

  //Delay 50ms before next reading.
  delay(50);
}


