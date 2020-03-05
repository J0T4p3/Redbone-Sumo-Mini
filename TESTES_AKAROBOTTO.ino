// Definição de portas motores e acelerador (stby para ligar o driver)
const int motorA1 = 7;
const int motorA2 = 8;
const int motorB1 = 4;
const int motorB2 = 5;
const int stby = 6;
const int acelA = 9;
const int acelB = 3;

// Definição de portas sensores
const int shp = A0;  // Sharp
const int ref1 = A1;  /// borda DIREITO
const int ref2 = A2;  /// borda ESQUERDO

void setup() {
  Serial.begin(9600);
  
//  Teste dos motores
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);

//  Aceleradores
  pinMode(acelA, OUTPUT);
  pinMode(acelB, OUTPUT);

  
//  Ativação stand by
  pinMode(stby, OUTPUT);
  digitalWrite(stby, HIGH);


//  Teste dos sensores
  pinMode(ref1, INPUT);
  pinMode(ref2, INPUT);
  pinMode(shp, INPUT);

//  5 segundos para iniciar
  delay(5000);
}

/* FUNÇÕES DE MOVIMENTAÇÃO*/
void frente(){
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
  analogWrite(acelA, 700); //DIREITA
  analogWrite(acelB, 700); //ESQUERDA
}

void tras(){
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  analogWrite(acelA, 1000);
  analogWrite(acelB, 1000);
}
void direita(){
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  analogWrite(acelA, 700);
  analogWrite(acelB, 300);

}

void esquerda(){
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
  analogWrite(acelA, 300);
  analogWrite(acelB, 700);
}

void freio(){
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, HIGH);
  analogWrite(acelA, 900);
  analogWrite(acelB, 900);
}
/* FUNÇÕES QUE SERÃO UTILIZADAS NO LOOP*/
// Corre ao redor da arena
void scape(int rf1, int rf2){
  if(rf1 > 300 && rf2 > 300){
    frente();
  }else if(rf1 < 300 && rf2 < 300){
    tras();
  }else if(rf1 < 300){
    direita();
  }else if(rf2 < 300){
    esquerda();
  }
}

//  Fica a procura de oponentes
void busca(int shp){
  if(shp > 300){
    frente();
  }
}

void loop() {
  int rf1 = analogRead(ref1);                                                                                                                                                                                        
  int rf2 = analogRead(ref2);
  Serial.print(rf1);
  Serial.print("     ");
  Serial.println(rf2);
  int shp = analogRead(shp);
  busca(shp); // função criada para procurar o adversário
  scape(rf1, rf2); // função criada para correr em volta do círculo da arena
  
}
