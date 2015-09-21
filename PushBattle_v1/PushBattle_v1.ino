const int stepPin = 3; 
const int dirPin = 4; 

void setup() {

  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
}

void loop() {
  digitalWrite(dirPin,HIGH);
  for(int i=0; i<1000; i++)  {  
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(100);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(100);
  }
  delay(100);

  digitalWrite(dirPin,LOW);
  for(int i=0; i<1000; i++)  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(100);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(100);
  }
  delay(100);
}
