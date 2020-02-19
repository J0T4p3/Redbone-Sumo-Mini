const int motorB1 = 12; /// digital 09
const int motorB2 = 13; /// digital 10
const int acelB = A1;

const int motorA1 = 14; /// digital 11
const int motorA2 = 15; /// digital 12
const int acelA = A0;

const int ref1 = A2; /// PORTA IR
const int ref2 = A6; /// PORTA LUMI_ESQ
const int ref3 = A7;  /// PORTA LUMI_DIR

void setup() {
  Serial.begin(9600);
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
  if ( velocidade > 0 ){
    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, HIGH);
    analogWrite(acelA, velocidade);
    analogWrite(acelB, velocidade); 
  }
  if ( velocidade < 0 ){
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, HIGH);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);
    analogWrite(acelA, (-1) * velocidade);
    analogWrite(acelB, (-1) * velocidade); }
  }

int sensorLumi(int sensor){
  return analogRead(sensor);
  }

int sensorIR(){
  return analogRead(ref2);
  }

void program1(int sensor){
  if( sensor < 300 ){
    front(100);
  }
  else if( sensor < 1000 ){
    front(500);
  }
  else{
    turn(500); 
    }
  }

void program2(int lumiE, int lumiD, int ir){
  if (lumiE < 500)
    turn(500);
  if (lumiD < 500)
    turn(-500);
  }

void loop() {
  // put your main code here, to run repeatedly:
  /*
  int lumi = sensorLumi(ref1);
  int ir = sensorIR();
  program1(lumi);
  */
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  pinMode(acelA, OUTPUT);
  ///Serial.println("KOE MUNDÃO DA PORRA");
}
