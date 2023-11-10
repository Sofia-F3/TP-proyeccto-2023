#include <TimerOne.h>
#include <Servo.h>

int mSeg;

//ULTRAS B
#define ECHO_A A1
#define TRIG_A A0
long duracionA;
int distanciaA;

//ULTRAS B
#define ECHO_B A3
#define TRIG_B A2
long duracionB;
int distanciaB;

//SEGMENTOS A
#define AA  52
#define AB  51
#define AC  50
#define AD  49
#define AE  48
#define AF  47
#define AG  46
int numeroA = 0; //por ahora son 7 palos

//SEGMENTOS A
#define BA  44
#define BB  43
#define BC  42
#define BD  41
#define BE  40
#define BF  39
#define BG  38
int numeroB = 7; //por ahora son 7 palos

//MAQUINA 7 segmentos y ultrasónicos
#define ESPERA 0
#define DETECTA 1
#define CAMBIO 2
int estadoMaqReac = ESPERA;

#define DIST_PALOS 30
#define TIEMPO_DETECT 6

int flag = 0;

//MAQUINA mover servos
#define OBTENER_NUMERO 0
#define MOD_SERVO 1
#define ESPERAR 2
int estadoMaquina = 0;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;

int num;

bool estado1 = false;
bool estado2 = false;
bool estado3 = false;
bool estado4 = false;
bool estado5 = false;
bool estado6 = false;
bool estado7 = false;

void ISR_timer (void) {
  mSeg++;
}

void setup() {
  Timer1.initialize(1000); //Configuro timer para que interrumpa cada 1 milisegundo.
  Timer1.attachInterrupt(ISR_timer);

  servo1.attach(2);
  servo2.attach(3);
  servo3.attach(4);
  servo4.attach(5);
  servo5.attach(6);
  servo6.attach(7);
  servo7.attach(8);

  servo1.write(180);
  servo2.write(180);
  servo3.write(180);
  servo4.write(180);
  servo5.write(180);
  servo6.write(180);
  servo7.write(180);

  pinMode(ECHO_A, INPUT);
  pinMode(ECHO_B, INPUT);
  pinMode(TRIG_A, OUTPUT);
  pinMode(TRIG_B, OUTPUT);

  pinMode(AA, OUTPUT);
  pinMode(AB, OUTPUT);
  pinMode(AC, OUTPUT);
  pinMode(AD, OUTPUT);
  pinMode(AE, OUTPUT);
  pinMode(AF, OUTPUT);
  pinMode(AG, OUTPUT);

  pinMode(BA, OUTPUT);
  pinMode(BB, OUTPUT);
  pinMode(BC, OUTPUT);
  pinMode(BD, OUTPUT);
  pinMode(BE, OUTPUT);
  pinMode(BF, OUTPUT);
  pinMode(BG, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  //moverServos();
  maquinaSERVOS();
  if (estado1 == true && estado2 == true && estado3 == true && estado4 == true && estado5 == true && estado6 == true && estado7 == true) {
    estado1 = false;
    estado2 = false;
    estado3 = false;
    estado4 = false;
    estado5 = false;
    estado6 = false;
    estado7 = false;
    servo1.write(180);
    servo2.write(180);
    servo3.write(180);
    servo4.write(180);
    servo5.write(180);
    servo6.write(180);
    servo7.write(180);
    Serial.println("Todos los servos a 180");
  }
  
  numeroA = 0;
  maquinaReaccion();
  sensores();
  numA();
  numB();
  if (flag == 1) {
    flag = 0;
    numeroB--;
  }
  if (numeroB < 0) {
    numeroB = 7;
  }

  // paso un tiempo desde q se tiro el palo y ninung sensor detecta --> numero++;
}

void maquinaReaccion() {
  switch (estadoMaqReac) {
    case ESPERA:
      if (distanciaB <= DIST_PALOS || distanciaA <= DIST_PALOS) {
        mSeg = 0;
        Serial.println("Hay palo");
        estadoMaqReac = DETECTA;
      }
      break;

    case DETECTA:
      if (distanciaB <= DIST_PALOS || distanciaA <= DIST_PALOS && mSeg  >= TIEMPO_DETECT) {
        estadoMaqReac = CAMBIO;
        Serial.println(flag);
      }

      if (distanciaB > DIST_PALOS || distanciaA > DIST_PALOS && mSeg  >= TIEMPO_DETECT) {
        estadoMaqReac = ESPERA;
      }
      break;

    case CAMBIO:
      if (distanciaB > DIST_PALOS || distanciaA > DIST_PALOS ) {
        flag = 1;
        estadoMaqReac = ESPERA;
      }
      break;
  }
}

void maquinaSERVOS() {
  switch (estadoMaquina) {
    case OBTENER_NUMERO:
      num = random(1, 8);
      Serial.println(num);
      mSeg = 0;
      estadoMaquina = MOD_SERVO;
      break;

    case MOD_SERVO:
      switch (num) {
        case 1:
          if (estado1 == false) {
            servo1.write(90);
            Serial.println("Servo 1 a 90");
            estado1 = true;
            estadoMaquina = ESPERAR;
          } else {
            estadoMaquina = OBTENER_NUMERO;
          }
          break;

        case 2:
          if (estado2 == false) {
            servo2.write(90);
            Serial.println("Servo 2 a 90");
            estado2 = true;
            estadoMaquina = ESPERAR;
          } else {
            estadoMaquina = OBTENER_NUMERO;
          }
          break;

        case 3:
          if (estado3 == false) {
            servo3.write(90);
            Serial.println("Servo 3 a 90");
            estado3 = true;
            estadoMaquina = ESPERAR;
          } else {
            estadoMaquina = OBTENER_NUMERO;
          }
          break;

        case 4:
          if (estado4 == false) {
            servo4.write(90);
            Serial.println("Servo 4 a 90");
            estado4 = true;
            estadoMaquina = ESPERAR;
          } else {
            estadoMaquina = OBTENER_NUMERO;
          }
          break;

        case 5:
          if (estado5 == false) {
            servo5.write(90);
            Serial.println("Servo 5 a 90");
            estado5 = true;
            estadoMaquina = ESPERAR;
          } else {
            estadoMaquina = OBTENER_NUMERO;
          }
          break;

        case 6:
          if (estado6 == false) {
            servo6.write(90);
            Serial.println("Servo 6 a 90");
            estado6 = true;
            estadoMaquina = ESPERAR;
          } else {
            estadoMaquina = OBTENER_NUMERO;
          }
          break;

        case 7:
          if (estado7 == false) {
            servo7.write(90);
            Serial.println("Servo 7 a 90");
            estado7 = true;
            estadoMaquina = ESPERAR;
          } else {
            estadoMaquina = OBTENER_NUMERO;
          }
          break;
      }
      break;

    case ESPERAR:
      if (mSeg > 1500) {
        estadoMaquina = OBTENER_NUMERO;
      }
      break;
  }
}

void moverServos() {
  servo1.write(90);
  delay(500);
  servo1.write(180);
  delay(500);

  servo2.write(90);
  delay(500);
  servo2.write(180);
  delay(500);

  servo3.write(90);
  delay(500);
  servo3.write(180);
  delay(500);

  servo4.write(90);
  delay(500);
  servo4.write(180);
  delay(500);

  servo5.write(90);
  delay(500);
  servo5.write(180);
  delay(500);

  servo6.write(90);
  delay(500);
  servo6.write(180);
  delay(500);

  servo7.write(90);
  delay(500);
  servo7.write(180);
  delay(500);
}


void sensores() {
  digitalWrite(TRIG_A, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_A, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_A, LOW);

  duracionA = pulseIn(ECHO_A, HIGH);
  distanciaA = duracionA * 0.034 / 2;


  digitalWrite(TRIG_B, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_B, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_B, LOW);

  duracionB = pulseIn(ECHO_B, HIGH);
  distanciaB = duracionB * 0.034 / 2;

  Serial.println("Distancia A: " + String(distanciaA) + "       Distancia B: " + String(distanciaB));
}

void segA (int a, int b, int c, int d, int e, int f, int g) {
  digitalWrite(AA, a);
  digitalWrite(AB, b);
  digitalWrite(AC, c);
  digitalWrite(AD, d);
  digitalWrite(AE, e);
  digitalWrite(AF, f);
  digitalWrite(AG, g);
}

void segB (int a, int b, int c, int d, int e, int f, int g) {
  digitalWrite(BA, a);
  digitalWrite(BB, b);
  digitalWrite(BC, c);
  digitalWrite(BD, d);
  digitalWrite(BE, e);
  digitalWrite(BF, f);
  digitalWrite(BG, g);
}

void numA() {
  switch (numeroA) {
    case 0 :
      segA (0, 0, 0, 0, 0, 1, 0);
      break;

    case 1 :
      segA (0, 1, 1, 0, 1, 1, 1);
      break;

    case 2 :
      segA (1, 0, 0, 0, 0, 0, 1);
      break;

    case 3 :
      segA (0, 0, 1, 0, 0, 0, 1);
      break;

    case 4 :
      segA (0, 1, 1, 0, 1, 0, 0);
      break;

    case 5 :
      segA (0, 0, 1, 1, 0, 0, 0);
      break;

    case 6 :
      segA (0, 0, 0, 1, 0, 0, 0);
      break;

    case 7 :
      segA(0, 1, 1, 0, 0, 1, 1);
      break;

    case 8 :
      segA(0, 0, 0, 0, 0, 0, 0);
      break;

    case 9 :
      segA(0, 0, 0, 0, 0, 0, 0);
      break;
  }
}

void numB() {
  switch (numeroB) {
    case 0 :
      segB (0, 0, 0, 0, 0, 0, 1);
      break;

    case 1 :
      segB (0, 1, 1, 0, 1, 1, 1);
      break;

    case 2 :
      segB (1, 0, 0, 0, 0, 1, 0);
      break;

    case 3 :
      segB (0, 0, 1, 0, 0, 1, 0);
      break;

    case 4 :
      segB (0, 1, 1, 0, 1, 0, 0);
      break;

    case 5 :
      segB (0, 0, 1, 1, 0, 0, 0);
      break;

    case 6 :
      segB (0, 0, 0, 1, 0, 0, 0);
      break;

    case 7 :
      segB(0, 1, 1, 0, 0, 1, 1);
      break;

    case 8 :
      segB (0, 0, 0, 0, 0, 0, 0);
      break;

    case 9 :
      segB (0, 0, 0, 0, 0, 0, 0);
      break;
  }
}
