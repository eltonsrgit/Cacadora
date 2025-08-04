#include <PS4Controller.h>  
#include "SumoIR.h"
#include "DRV8833.h"
#include "sensoresIR.h"
#include "ledFX.h"  
#include "WildSide.h"
#define boot 0

int strategy = 0; // estrategia


// DRV8833 motor(motor_esq_1, motor_esq_2, motor_dir_1, motor_dir_2);


#include "TornadoOfSouls.h"
#include "RCDualShock.h"

SumoIR IR;

unsigned long tempoPressionado = 0;  // armazena o tempo que o botão foi pressionado
bool botaoPressionado = false;       // indica se o botão foi pressionado


void setup(){
  pinMode(boot, INPUT_PULLUP);
  Serial.begin(115200);
  IR.begin(15);
  PS4.begin("9c:30:5b:fb:f4:58");  // mac do meu ps4 "60:5b:b4:7e:74:a4" #### mac do pc "9c:30:5b:fb:f4:58"
  motor.begin();
  motor.bip(3, 200, 2000);
  pinMode(leftIRpin, INPUT);
  pinMode(rightIRpin, INPUT);

  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'
  
  pixels.begin();
  pixels.setBrightness(80);
  pixels.clear();
  ledLight(0, 0, 0);
  motor.stop();
}



void loop(){

  // Verifica se o botão foi pressionado
  if (digitalRead(boot) == LOW && !botaoPressionado) {
    tempoPressionado = millis();  // Armazena o tempo atual
    botaoPressionado = true;      // Marca o botão como pressionado
  }

  // Verifica se o botão foi pressionado por mais de 1000ms (1 segundo)
  if (botaoPressionado && (millis() - tempoPressionado >= 1000) && modoAutonomo && !RC) {
    modoAutonomo = false;  // Alterna o modo
    Serial.print("Modo alternado para: ");
    Serial.println(modoAutonomo ? "Autônomo." : "RC.");

    // Reseta a variável do botão pressionado
    botaoPressionado = false;
  }
  if (botaoPressionado && (millis() - tempoPressionado >= 1000) && !modoAutonomo && RC) {
    modoAutonomo = true;  // Alterna o modo
    Serial.print("Modo alternado para: ");
    Serial.println(modoAutonomo ? "Autônomo. " : "RC. ");
    // Reseta a variável do botão pressionado
    botaoPressionado = false;
  }
  

  if (!modoAutonomo) {
    RC = true;
    // Código RC
    DualShock();
    


  } else if (modoAutonomo) {
    // Código autônomo
    RC = false;
    PS4.setLed(255, 255, 255);   // seta a cor do led do controle
    PS4.sendToController();  // necessário para enviar o comando acima para o controle

    IR.update();

    // if( IR.available() ){
    //   int cmd = IR.read();
    //   if( cmd >= 4 && cmd <= 9 ){ // faixa de valores validos ( lembrando que 1, 2 e 3 são eservados pra start, stop e prepare)
    //     strategy = cmd;
    //     ledLight(200, 100, 100);
    //   }
    // }


    if (IR.prepare()) {

      motor.stop();
      ledLight(100, 100, 100);
      Serial.println("-> sumo prepare");

    } else if (IR.start()) {
      Serial.println("-> sumo start");

      
    } else if (IR.on()) {
      pixels.clear();
      ledLight(0, 150, 0);

      switch (strategy){
        case 4:
          TornadoOfSouls_L();
        break;

        case 5:
          TornadoOfSouls_R();
        break;

        case 6:
          WildSide();
        break;

        case 7:
          motor.move(-1023, -1023);
        break;

        default:
        motor.stop();
        break;
        // ... outras estratégias
      }
      

    } else if (IR.stop()) {
      pixels.clear();
      motor.stop();
      Serial.println("-> sumo stop");
      ledDetection();

    } else  {
      strategyLED(); // vermelho para estratégia 4, branco para 5 e azul para 6
      
      ledDetection();
      
    }
  }
}

void strategyLED(){
  int cmd = IR.read();
  if (cmd >= 4 && cmd <= 9) { // faixa de valores validos ( 1, 2 e 3 são reservados pra prepare, start e stop)
    strategy = cmd;
  } else return;

  if (cmd <= 8) {
    const int num_leds = cmd % 8;
    for(uint8_t i = 0; i < num_leds; i++) {
      switch ((cmd-3) % 5) { // Acende o LED de 0 ao número comando numa cor +- diferente cada número
        case 0: pixels.setPixelColor(i, pixels.Color(150, 0,   0  )); break;
        case 1: pixels.setPixelColor(i, pixels.Color(150, 150, 150)); break;
        case 2: pixels.setPixelColor(i, pixels.Color(0,   0,   150)); break;
        case 3: pixels.setPixelColor(i, pixels.Color(255, 150, 0  )); break;
        case 4: pixels.setPixelColor(i, pixels.Color(0,   150, 255)); break;
      } pixels.show();
    }
    delay(80);
    for(uint8_t i = 0; i < num_leds; i++) { 
      pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Desliga os LEDs
      pixels.show();
    }
    delay(80);
  }
  // if (cmd == 4) {
  //   for(uint8_t i = 0; i < cmd; i++) { 
  //     pixels.setPixelColor(i, pixels.Color(150, 0, 0)); // Acende o LED de 1 a 4 em vermelho
  //     pixels.show();      
  //   }
  //   delay(80);
  //   for(uint8_t i = 0; i < cmd; i++) { 
  //     pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Acende o LED de 1 a 4 em vermelho
  //     pixels.show();          
  //   }
  //   delay(80);
  // }
  // if (cmd == 5) {
  //   for(uint8_t i = 0; i < cmd; i++) { 
  //     pixels.setPixelColor(i, pixels.Color(150, 150, 150)); // Acende o LED de 1 a 4 em vermelho
  //     pixels.show();    
  //   }
  //   delay(80);
  //   for(uint8_t i = 0; i < cmd; i++) { 
  //     pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Acende o LED de 1 a 4 em vermelho
  //     pixels.show();          
  //   }
  //   delay(80);
  // }

  // if (cmd == 6) {
  //   for(uint8_t i = 0; i < cmd; i++) { 
  //     pixels.setPixelColor(i, pixels.Color(0, 0, 150)); // Acende o LED de 1 a 4 em vermelho
  //     pixels.show();    
  //   }
  //    delay(80);
  //   for(uint8_t i = 0; i < cmd; i++) { 
  //     pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Acende o LED de 1 a 4 em vermelho
  //     pixels.show();          
  //   }
  //   delay(80);
  // }

  // if (cmd == 7) {
  //   for(uint8_t i = 0; i < cmd; i++) { 
  //     pixels.setPixelColor(i, pixels.Color(255, 150, 0)); // Acende o LED de 1 a 4 em vermelho
  //     pixels.show();    
  //   }
  //    delay(80);
  //   for(uint8_t i = 0; i < cmd; i++) { 
  //     pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Acende o LED de 1 a 4 em vermelho
  //     pixels.show();          
  //   }
  //   delay(80);
  // }
  // if (cmd == 8) {
  //   for(uint8_t i = 0; i < cmd; i++) { 
  //     pixels.setPixelColor(i, pixels.Color(150, 150, 150)); // Acende o LED de 1 a 4 em vermelho
  //     pixels.show();    
  //   }
  //    delay(80);
  //   for(uint8_t i = 0; i < cmd; i++) { 
  //     pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Acende o LED de 1 a 4 em vermelho
  //     pixels.show();          
  //   }
  //   delay(80);
  // }
}
