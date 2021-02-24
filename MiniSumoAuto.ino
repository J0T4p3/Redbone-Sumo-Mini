// LED
#define LED 6

// left motor
#define pwmL 9
#define leftMotor1 7
#define leftMotor2 8

// right motor
#define pwmR 3
#define rightMotor1 5
#define rightMotor2 4

// DIP switch
#define DIP1 10
#define DIP2 11
#define DIP3 12
#define DIP4 13

// Robocore's line sensor
#define lineL A0
#define lineR A1

// Jsumo's distance sensor
#define distL A2
#define distR A3

// Jsumo's micro-start
#define microST 2
/*******PINOUT DEFINES - END*********/

/*******FUNCTIONS*******/
void MotorL(int pwm); // motor esquerdo
void MotorR(int pwm); // motor direito
int readDIP();        // ler chave DIP
void sensorBordaArco();   // ler os senores de cor
void sensorBordaRetorno(); // ler os senores de cor
void rodaEbusca();    // busca do oponente
void rodaEbuscaEsquerda(); //Vira primeiro pra esquerda
void rodaEbuscaDireita();  //Vira primeiro pra direita
/*******FUNCTIONS - END*******/

void setup() {

  /****************PINOUT CONFIG****************/
  // OUTPUTS
  pinMode(LED, OUTPUT);         // led

  // right motor
  pinMode(pwmR, OUTPUT);        // right motor power
  pinMode(rightMotor1, OUTPUT); // right motor dir.
  pinMode(rightMotor2, OUTPUT); // right motor dir.

  // left motor
  pinMode(pwmL, OUTPUT);        // left motor power
  pinMode(leftMotor1, OUTPUT);  // left motor dir.
  pinMode(leftMotor2, OUTPUT);  // left motor dir.

  // DIP switch
  pinMode(DIP1, INPUT_PULLUP);
  pinMode(DIP2, INPUT_PULLUP);
  pinMode(DIP3, INPUT_PULLUP);
  pinMode(DIP4, INPUT_PULLUP);

  // line sensor
  pinMode(lineL, INPUT);
  pinMode(lineR, INPUT);

  // distance sensor
  pinMode(distR, INPUT);
  pinMode(distL, INPUT);

  // micro-start
  pinMode(microST, INPUT);
  /****************PINOUT CONFIG - END***************/

  /***************INITIAL CONDITIONS*****************/
  digitalWrite(LED, LOW); // LED off / LED desligado / LED apagado
  delay(2000);
  int c = 0;
  while (c < readDIP()) { // Pisca o LED de acordo com o valor DIP selecionado
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED, LOW);
    delay(250);
    c++;
  }
  MotorL(0); // motor esquerdo parado
  MotorR(0); // motor direito parado
  /*************INITIAL CONDITIONS - END*************/
}

/* ================ VOID LOOP ====================*/

void loop() {
  while (digitalRead(microST) == HIGH) { // Enquanto o controlador estiver enviando sinal, o código irá rodar
    //---DIP (DEFAULT) 1111--- 
    if (readDIP() == 15) { // DIP 1111 - Ir pra frente com tudo e depois procurar o adversário
      MotorR(255);
      MotorL(255);
      delay(450);
      while (true) { // Após realizar o primeiro movimento, inicar processo de busca
        while (lineR > 700 && lineL > 700) {
          rodaEbusca();
        }
        sensorBordaArco();
      }
    }
    //---end - DIP 1111---

    //---DIP 1110--- 
    if (readDIP() == 14) { // DIP 1111 - Ir pra frente com tudo e depois procurar o adversário
      MotorR(255);
      MotorL(255);
      delay(450);
      while (true) { // Após realizar o primeiro movimento, inicar processo de busca
        while (lineR > 700 && lineL > 700) {
          rodaEbusca();
        }
        sensorBorda();
      }
    }
    //---end - DIP 1110---

    //---DIP 0001---
    if (readDIP() == 1) { // DIP 0001 - Fazer uma meia lua da esquerda pra direita e depois procurar
      MotorL(255);
      MotorR(100);
      delay(500);
      while (true) {
        while (lineR > 700 && lineL > 700) {
          rodaEbuscaDireita();
        }
        sensorBorda();
      }
    }
    //---end - DIP 0001---

    //---DIP 0010---
    if (readDIP() == 2) { // DIP 0010 - Fazer uma meia lua da direita pra esquerda e depois procurar
      MotorL(100);
      MotorR(255);
      delay(500);
      while (true) {
        while (lineR > 700 && lineL > 700) {
          rodaEbuscaEsquerda();
        }
        sensorBorda();
      }
    }
    //---end - DIP 0010---


    //---DIP 0011---
    
    //---end - DIP 0011---

  }
}

/* ================ end - VOID LOOP ==================*/

/**CONTROLE DO MOTOR ESQUERDO**/
// pwm = 0 -> parado
// 0<pwm<=255 -> para frente
// -255<=pwm<0 -> para tras
void MotorL(int pwm) {
  // leftMotor1=0 and leftMotor2=0 -> stopped / parado / parado
  // leftMotor1=0 and leftMotor2=1 -> moves forward / avanca / avanzar
  // leftMotor1=1 and leftMotor2=0 -> moves back / recua / retrocede
  // leftMotor1=1 and leftMotor2=1 -> stopped (braked) / parado (travado) / parado (frenado)

  if (pwm == 0) {
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
  }
  else if (pwm < 0)
  {
    analogWrite(pwmL, -pwm);
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
  }
  else
  {
    analogWrite(pwmL, pwm);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
  }
}


/**CONTROLE DO MOTOR DIREITO**/
// pwm = 0 -> parado
// 0<pwm<=255 -> frente
// -255<=pwm<0 -> tras
void MotorR(int pwm) {
  // rightMotor1=0 and rightMotor2=0 -> parado
  // rightMotor1=0 and rightMotor2=1 -> avanca
  // rightMotor1=1 and rightMotor2=0 -> retrocede
  // rightMotor1=1 and rightMotor2=1 -> parado (travado)

  if (pwm == 0) {
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
  }
  else if (pwm < 0)
  {
    analogWrite(pwmR, -pwm);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
  }
  else
  {
    analogWrite(pwmR, pwm);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
  }
}

/** ler chave DIP**/
// retorna um valor entre 0 e 15
int readDIP() {
  int n = 0;
  if (digitalRead(DIP4) == HIGH)
    n = 1;
  if (digitalRead(DIP3) == HIGH)
    n |= (1 << 1);
  if (digitalRead(DIP2) == HIGH)
    n |= (1 << 2);
  if (digitalRead(DIP1) == HIGH)
    n |= (1 << 3);
  return n;
}

void sensorBordaArco() { // Ao identificqr a bora em um dos lados, gira o robô de volta para o dojo
  if (lineL < 700) {
    MotorL(255);
    MotorR(10);
    delay(100);
  } else if (lineR < 700) {
    MotorL(10);
    MotorR(255);
    delay(100);
  }
}

void sensorBordaRetorno() { // Ao identificqr a bora em um dos lados, gira o robô de volta para o dojo
  if (lineL < 700) {
    MotorL(255);
    MotorR(10);
    delay(100);
  } else if (lineR < 700) {
    MotorL(10);
    MotorR(255);
    delay(100);
  }
}

/** Funções de busca **/
// Rodando em torno do proprio eixo buscando o inimigo
void rodaEbusca() {
  while (digitalRead(microST) == HIGH) {
    while (distL == LOW && distR == LOW) {
      if (random(0, 1) == 0) { //Escolhe um lado aleatório para rodar e procurar
        MotorL(100);
        MotorR(30);
      } else {
        MotorL(30);
        MotorR(100);
      }
    }
    while (distL == HIGH || distR == HIGH) { //Se alguém é visto pelos dois sensores, para frente direto. Se apenas por um,
      if (distL == HIGH && distR == HIGH) { //então penderá para o lado que foi visto.
        MotorL(255);
        MotorR(255);
      } else if (distL == HIGH) {
        MotorL(180);
        MotorR(255);
      } else if (distR == HIGH) {
        MotorL(255);
        MotorR(180);
      }
    }
  }
}

void rodaEbuscaDireita() {
  while (digitalRead(microST) == HIGH) {
    while (distL == LOW && distR == LOW) {
      MotorL(100);
      MotorR(30);
    }
    while (distL == HIGH || distR == HIGH) { //Se alguém é visto pelos dois sensores, para frente direto. Se apenas por um,
      if (distL == HIGH && distR == HIGH) { //então penderá para o lado que foi visto.
        MotorL(255);
        MotorR(255);
      } else if (distL == HIGH) {
        MotorL(180);
        MotorR(255);
      } else if (distR == HIGH) {
        MotorL(255);
        MotorR(180);
      }
    }
  }
}

void rodaEbuscaEsquerda() {
  while (digitalRead(microST) == HIGH) { 
    while (distL == LOW && distR == LOW) {
      MotorL(10);
      MotorR(80);
    }
  }
  while (distL == HIGH || distR == HIGH) { //Se alguém é visto pelos dois sensores, para frente direto. Se apenas por um,
    if (distL == HIGH && distR == HIGH) { //então penderá para o lado que foi visto.
      MotorL(255);
      MotorR(255);
    } else if (distL == HIGH) {
      MotorL(180);
      MotorR(255);
    } else if (distR == HIGH) {
      MotorL(255);
      MotorR(180);
    }
  }
}
