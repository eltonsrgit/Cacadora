#ifndef ledFX_H
#define ledFX_H 

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN 2 // pino do anel de leds
#define NUMPIXELS 8 // quantidade de leds do anel

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800); // necessário
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

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


#endif
