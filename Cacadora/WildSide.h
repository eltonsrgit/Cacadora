#ifndef WildSide_H
#define WildSide_H

#include "sensoresIR.h"
#include "DRV8833.h"
#include "TornadoOfSouls.h"

#define LsumoLeft 27
#define LsumoRight 14

int leftRay = 0;
int rightRay = 0;

bool EsqAtv, DirAtv;
bool girando = false;

enum soma {
  Esquerda = -1,
  Nada,
  Direita,
  Tudo
};

void lerSensores() {
  leftRay = digitalRead(LsumoLeft);
  rightRay = digitalRead(LsumoRight);
}

void WildSide() {
  lerSensores();
  int reaction = -leftRay + rightRay;

  // Verifica se nenhum objeto foi detectado
  if (reaction == Nada && !girando) {
    // Move para frente
    motor.move(900, 900);
    Serial.println("Avançando...");
  } else {
    // Se algo for detectado, faz as ações já definidas
    switch (reaction) {
      case Esquerda:
        motor.move(-1023, 1023);
        EsqAtv = true;
        DirAtv = false;
        girando = true;
        Serial.println("Inimigo à Esquerda!");
        break;
      
      case Direita:
        motor.move(1023, -1023);
        EsqAtv = false;
        DirAtv = true;
        girando = true;
        Serial.println("Inimigo à Direita!");
        break;
      
      case Nada:
        TornadoOfSouls_R();
        EsqAtv = false;
        DirAtv = false;
        Serial.println("Seek and Destroy?");
        break;
      
      case Tudo:
        motor.stop();
        EsqAtv = true;
        DirAtv = true;
        girando = false;
        Serial.println("Tô lutando contra dois?");
        break;
    }
  }
}



#endif
