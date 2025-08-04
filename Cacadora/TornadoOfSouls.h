#ifndef TornadoOfSouls_H
#define TornadoOfSouls_H

#include "DRV8833.h"

const int motor_esq_1 = 4;   //4 vespa
const int motor_esq_2 = 23;  //27 vespa
const int motor_dir_1 = 18;  //13 vespa
const int motor_dir_2 = 19;  //14 vespa

DRV8833 motor(motor_esq_1, motor_esq_2, motor_dir_1, motor_dir_2);

int EstadoAtual;

void EstadoUpdate(){  // função que atualiza os estados

  EstadoAtual = 1; // sem inimigo

  if ( LeftDetection() && RightDetection()){  // enxergando inimigo com os 2 sensores
    EstadoAtual = 2;
  } else if ( LeftDetection() ){ // enxergando com o direito
    EstadoAtual = 3;
  } else if (RightDetection()){ // enxergando com o esquerdo
    EstadoAtual = 4;
  }
   else {
    EstadoAtual = 1; // sem inimigo
  }
}

void TornadoOfSouls(){  // maquina de estados
  EstadoUpdate(); // função atualiza o estado a todo momento
  switch (EstadoAtual){
    case 1:
      Serial.println("Searching Enemy...");
      motor.move(900,-900);
      break;

    case 2:
      Serial.println("ROBOT ATTACK!");
      motor.move(1023, 1023);
      break;

    case 3:
      Serial.println("Left Detected!");
      motor.move(-1023, 1023);
      break;

    case 4:
      Serial.println("Right Detected!");
      motor.move(1023, -1023);
      break;       
  }
}

void TornadoOfSouls_L(){  // maquina de estados
  EstadoUpdate(); // função atualiza o estado a todo momento
  switch (EstadoAtual){
    case 1:
      Serial.println("Searching Enemy...");
      motor.move(-800, 800);
      break;

    case 2:
      Serial.println("ROBOT ATTACK!");
      motor.move(1023, 1023);
      break;

     case 3:
       Serial.println("Left Detected!");
       motor.move(-1023, 1023);
       break;

    case 4:
      Serial.println("Right Detected!");
      motor.move(1023, -1023);
      break;
  }
}


void TornadoOfSouls_R(){  // maquina de estados
  EstadoUpdate(); // função atualiza o estado a todo momento
  switch (EstadoAtual){
    case 1:
      Serial.println("Searching Enemy...");
      motor.move(800, -800);
      break;

    case 2:
      Serial.println("ROBOT ATTACK!");
      motor.move(1023, 1023);
      break;

    case 3:
      Serial.println("Left Detected!");
      motor.move(1023, -1023);
      break;

    case 4:
      Serial.println("Right Detected!");
      motor.move(-1023, 1023);
      break;
  }
}

#endif
