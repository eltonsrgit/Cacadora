#ifndef ledFX_H
#define ledFX_H 
#include "sensoresIR.h"
#include <Adafruit_NeoPixel.h>
#include "WildSide.h"
#define PIN 2 // pino do anel de leds
#define NUMPIXELS 8 // quantidade de leds do anel
#define LED3 3
#define LED4 4
#define LED7 7
#define LED1 0
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800); // necessário
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);

void ledBlink(uint8_t r, uint8_t g, uint8_t b, int time) { // pisca todas os leds em um intervalo de tempo
  pixels.clear();
  for(uint8_t i = 0; i < NUMPIXELS; i++) { 
    pixels.setPixelColor(i, pixels.Color(r, g, b));
    pixels.show();   
  }
  pixels.clear();
  delay(time);
  for(uint8_t i = 0; i < NUMPIXELS; i++) { 
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    pixels.show();    
  }
  delay(time);
}

/*----------------------------------------------------------------------------------------*/
void ledLight (uint8_t r, uint8_t g, uint8_t b) { // luz contínua
  pixels.clear();
  for(uint8_t i = 0; i < NUMPIXELS; i++) { 
    pixels.setPixelColor(i, pixels.Color(r, g, b));
    pixels.show();    
  }
}

/*----------------------------------------------------------------------------------------*/
void ledCircle(uint8_t r, uint8_t g, uint8_t b, int time) { // luzes "andam" em círculo numa certa velocidade dependendo do tempo
  pixels.clear();
  for(uint8_t i = 0; i < NUMPIXELS; i++) { 
    pixels.setPixelColor(i, pixels.Color(r, g, b));
    pixels.show();    
    delay(time);
    pixels.clear(); 
  }
}

/*----------------------------------------------------------------------------------------*/
void ledCircleBlink(uint8_t r, uint8_t g, uint8_t b, int time) { // luzes "andam" em círculo e piscam no final numa certa velocidade dependendo do tempo
  pixels.clear();
  for(uint8_t i = 0; i < NUMPIXELS; i++) { 
    pixels.setPixelColor(i, pixels.Color(r, g, b));
    pixels.show();    
  }
  for(uint8_t i = 0; i < NUMPIXELS; i++) { 
    pixels.setPixelColor(i, pixels.Color(r, g, b));
    pixels.show();
    delay(time);
    pixels.clear();
  }
}


void ledPatrol(uint8_t r, uint8_t g, uint8_t b, uint8_t r2, uint8_t g2, uint8_t b2, int time) { // luzes "andam" em círculo e piscam no final numa certa velocidade dependendo do tempo
  pixels.clear();
  for(int i = 0; i < NUMPIXELS; i++) { 
    pixels.clear();
    pixels.setPixelColor(i, pixels.Color(r, g, b));
    pixels.show();
    delay(time);
  }
  for(int i = NUMPIXELS; i > 0; i--) { 
    pixels.clear();
    pixels.setPixelColor(i, pixels.Color(r2, g2, b2));
    pixels.show();
    delay(time);
  }
  for(int i = 0; i < NUMPIXELS; i++){
    pixels.setPixelColor(i+1, pixels.Color(150, 150, 150));
    pixels.show();
  }
  delay(time);
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}





void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}


void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}


void setDefaultColor(uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(r, g, b));
    }
  }

void ledDetection() {

  
  
  setDefaultColor(150, 0, 0); // Define a cor padrão azul para todos os LEDs
  
  if (LeftDetection()) {
    Serial.println("ESQUERDA FRONTAL DETECTADO");
    pixels.setPixelColor(LED4, pixels.Color(0, 150, 0)); // Acende o LED 4 em vermelho

    } if (RightDetection()) {
    Serial.println("DIREITA FRONTAL DETECTADO");
    pixels.setPixelColor(LED3, pixels.Color(0, 150, 0)); // Acende o LED 5 em vermelho
    }
    lerSensores();
    if (leftRay == 1) {
    Serial.println("ESQUERDA LATERAL DETECTADO");
    pixels.setPixelColor(LED7, pixels.Color(0, 0, 150)); // Acende o LED 5 em vermelho

    }
    if (rightRay == 1) {
    Serial.println("DIREITA LATERAL DETECTADO");
    pixels.setPixelColor(LED1, pixels.Color(0, 0, 150)); // Acende o LED 5 em vermelho
    }

   else {
    Serial.println("PROCURANDO OBJETO");
  }
  
  pixels.show();
  delay(10);
}
#endif