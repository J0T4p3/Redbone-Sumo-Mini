const int motorA1 = 2;
const int motorA2 = 3;
const int motorB1 = 8;
const int motorB2 = 9;
const int acelA = A0;
const int acelB = A1;
const int ref1 = A2;
const int ref2 = A3;

void setup() {
  
   pinMode(motorA1, OUTPUT);  
   pinMode(motorA2, OUTPUT);  
   pinMode(motorB1, OUTPUT);  
   pinMode(motorA2, OUTPUT);  
   pinMode(acelA, OUTPUT);
   pinMode(acelB, OUTPUT);
   pinMode(ref1, INPUT);
   pinMode(ref2, INPUT);
   
}

void front(int velocidade){
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  analogWrite(acelA, velocidade);
  analogWrite(acelB, velocidade); 
  }

void back(int velocidade){
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
  analogWrite(acelA, velocidade);
  analogWrite(acelB, velocidade); 
  }

void turn(int velocidade){
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
  analogWrite(acelA, velocidade);
  analogWrite(acelB, velocidade); 
  }

void loop() {
  // put your main code here, to run repeatedly:
  int t = analogRead(ref1);
  if(t<500){
    front(500);
  }
  else if( t < 1000 ){
    back(500);
  }
  else{
    analogWrite(acelA, 0);
    analogWrite(acelB, 0); 
    }
}
