//Código base Smart Car Arduino
//Servo, Sensor, Bluetooth

// Alexandre Garcez Vieira
// tecagv@terra.com.br
// Skype: tecagv@live.com
// Licença: CC BY-NC-SA
// https://br.creativecommons.org/

#include <Servo.h>
Servo servo1;

int izqA = 10; //Ponte H
int izqB = 12;
int derA = 11;
int derB = 13;

int vel = 255; //Velocidade

int estado = 'c'; //Estado inicial (Parado)

int pecho = 2;  // Sensor Ultrassonico
int ptrig = 3;

int duracion, distancia;

int pisca[] = {4, 7, 8, 13}; // Pisca Alerta
int contador = 0;
int timer = 100; //1000 = 1 Segundo

void setup()  {

  Serial.begin(9600);
  pinMode(derA, OUTPUT);
  pinMode(derB, OUTPUT);
  pinMode(izqA, OUTPUT);
  pinMode(izqB, OUTPUT);

  pinMode(pecho, INPUT);
  pinMode(ptrig, OUTPUT);

  pinMode(13, OUTPUT); //Led do Sensor Ultrassonico
  pinMode(7, OUTPUT); //Pisca Farol
  pinMode(8, OUTPUT); //Pisca Farol
  pinMode(4, OUTPUT); //Buzina


  servo1.attach(11);
  servo1.write(101);

  {
    for (contador = 0; contador < 4; contador++) {
      pinMode(pisca[contador], OUTPUT);
    }
  }
}

void loop()  {

  if (Serial.available() > 0) {
    estado = Serial.read();
  }
  if (estado == 'a') {       //Frente
    analogWrite(derB, 0);
    analogWrite(izqB, 0);
    analogWrite(derA, vel);
    analogWrite(izqA, vel);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);

  }
  if (estado == 'b') {      //Esquerda
    analogWrite(derB, 0);
    analogWrite(izqB, 0);
    analogWrite(derA, 0);
    analogWrite(izqA, vel);
    //digitalWrite(50, LOW);
  }
  if (estado == 'c') {
    analogWrite(derB, 0);
    analogWrite(izqB, 0);
    analogWrite(derA, 0);
    analogWrite(izqA, 0);
    digitalWrite(7, LOW); //Pisca
    digitalWrite(8, LOW); //Pisca
    digitalWrite(4, LOW); //Buzina
    digitalWrite(13, LOW); //LED
    //digitalWrite(50, HIGH);
    //servo1.write(101);
  }
  if (estado == 'd') {      //Direita
    analogWrite(derB, 0);
    analogWrite(izqB, 0);
    analogWrite(izqA, 0);
    analogWrite(derA, vel);
    //digitalWrite(50, LOW);
  }

  if (estado == 'e') {      //Atrás
    analogWrite(derA, 0);
    analogWrite(izqA, 0);
    analogWrite(derB, vel);
    analogWrite(izqB, vel);
    //digitalWrite(50, LOW);
  }

  if (estado == 'f') {          //Auto

    digitalWrite(ptrig, HIGH);
    delay(0.01);
    digitalWrite(ptrig, LOW);

    duracion = pulseIn(pecho, HIGH);
    distancia = (duracion / 2) / 29;
    delay(10);

    if (distancia <= 30 && distancia >= 2) {
      digitalWrite(13, HIGH);

      analogWrite(derB, 0);
      analogWrite(izqB, 0);
      analogWrite(derA, 0);
      analogWrite(izqA, 0);
      delay (200);

      analogWrite(derB, vel);
      analogWrite(izqB, vel);
      delay(500);

      analogWrite(derB, 0);
      analogWrite(izqB, 0);
      analogWrite(derA, 0);
      analogWrite(izqA, vel);
      delay(600);

      digitalWrite(13, LOW);
    }
    else {
      analogWrite(derB, 0);
      analogWrite(izqB, 0);
      analogWrite(derA, vel);
      analogWrite(izqA, vel);
    }
  }
  if (estado == 'g') {
    servo1.write(30);
    delay(1000);

    servo1.write(90);
    delay(700);

    servo1.write(150);
    delay(700);
  }
  if (estado == 'h') {
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(13, HIGH);
  }
  if (estado == 'm') {
    digitalWrite(13, 0);
  }
  if (estado == 'i') {
    digitalWrite(30, HIGH);
  }
  if (estado == 'n') {
    digitalWrite(derB, 0);
  }
  if (estado == 'z') {    
    digitalWrite(4, HIGH); // Buzina
  }
  if (estado == 'o') {
    digitalWrite(derA, 0);
  }
  if (estado == 'k') {
    digitalWrite(izqB, 1);
  }
  if (estado == 'p') {
    digitalWrite(izqB, 0);
  }
  if (estado == 'l') {
    digitalWrite(izqA, 1);
  }
  if (estado == 'q') {
    for (contador = 0; contador < 4; contador++) {
      digitalWrite(pisca[contador], HIGH);
      delay(timer);
      digitalWrite(pisca[contador], LOW);
      delay(timer);
    }
  }
}
