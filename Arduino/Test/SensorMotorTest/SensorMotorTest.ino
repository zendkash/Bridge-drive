#define fliPin 0
#define floPin 1
#define friPin 2
#define froPin 3

#define usrTrigPin 12
#define usrEchoPin 13
#define uslTrigPin 2
#define uslEchoPin 3

#define EN1 6
#define EN2 5
#define IN1 7
#define IN2 4

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
char val;

void setup()
{
  Serial.begin(9600);

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

void Motor1(int pwm, boolean reverse) {
  analogWrite(EN1,pwm); //set pwm control, 0 for stop, and 255 for maximum speed
  if(reverse) { 
    digitalWrite(IN1,HIGH);    
  }
  else {
    digitalWrite(IN1,LOW);    
  }
}  

void Motor2(int pwm, boolean reverse) {
  analogWrite(EN2,pwm);
  if(reverse) {
    digitalWrite(IN2,HIGH);
  }
  else
  {
    digitalWrite(IN2,LOW);    
  }
}  

void loop()
{
  time=micros();
  //USL
  /* The following trigPin/echoPin cycle is used to determine the
   distance of the nearest object by bouncing soundwaves off of it. */
  digitalWrite(uslTrigPin, LOW); 
  delayMicroseconds(2); 

  digitalWrite(uslTrigPin, HIGH);
  delayMicroseconds(10); 

  digitalWrite(uslTrigPin, LOW);
  lDuration = pulseIn(uslEchoPin, HIGH);

  //Calculate the distance (in cm) based on the speed of sound.
  lDistance = lDuration/58.2;

  //USR
  /* The following trigPin/echoPin cycle is used to determine the
   distance of the nearest object by bouncing soundwaves off of it. */
  digitalWrite(usrTrigPin, LOW); 
  delayMicroseconds(2); 

  digitalWrite(usrTrigPin, HIGH);
  delayMicroseconds(10); 

  digitalWrite(usrTrigPin, LOW);
  rDuration = pulseIn(usrEchoPin, HIGH);

  //Calculate the distance (in cm) based on the speed of sound.
  rDistance = rDuration/58.2;

  //Read QRDs
  fli = analogRead(fliPin);
  flo = analogRead(floPin);
  fri = analogRead(friPin);
  fro = analogRead(froPin);

  //Read encoders
  encLA = digitalRead(encLAPin);
  encLB = digitalRead(encLBPin);
  encRA = digitalRead(encRAPin);
  encRB = digitalRead(encRBPin);

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

  val = Serial.read();
  if(val!=-1)
  {
    switch(val)
    {
    case 'w'://Move ahead
      Motor1(255,true);  //You can change the speed, such as Motor(50,true)
      Motor2(255,true);

      break;
    case 'x'://move back
      Motor1(255,false);
      Motor2(255,false);
      break;
    case 'a'://turn left
      Motor1(255,false);
      Motor2(255,true);
      break;
    case 'd'://turn right
      Motor1(255,true);
      Motor2(255,false);
      break;   
    case 's'://stop
      Motor1(0,false);
      Motor2(0,false);
      break;
    }
  }
}





