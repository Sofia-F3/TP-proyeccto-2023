#include <TimerOne.h>
#include <Servo.h>

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

int seg = 0;
int num;

bool estado1 = false;
bool estado2 = false;
bool estado3 = false;
bool estado4 = false;
bool estado5 = false;
bool estado6 = false;
bool estado7 = false;

void TIMER (void) {
  seg++;
}

void setup() {
  Serial.begin(9600);
  servo1.attach(2);
  servo2.attach(3);
  servo3.attach(4);
  servo4.attach(5);
  servo5.attach(6);
  servo6.attach(7);
  servo7.attach(8);
  Timer1.initialize(1000);
  Timer1.attachInterrupt(TIMER);
}

void loop() {
  maquina();

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
}

void maquina() {
  switch (estadoMaquina) {
    case OBTENER_NUMERO:
      num = random(1, 8);
      Serial.println(num);
      seg = 0;
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
      if (seg > 1500) {
        estadoMaquina = OBTENER_NUMERO;
      }
      break;
  }
}
