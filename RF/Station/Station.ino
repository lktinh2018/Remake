#include <SPI.h>
#include "RF24.h"

//Pin 
#define LED_PIN 8
#define RELAY_PIN 7
#define BUTTON_PIN 3

//RF module
const uint64_t pipe = 0xE8E5F0F0E1LL;
RF24 radio(9,10);
byte count = 0; 
byte msgTrans[10] = "Hello";


//Relay module
byte activatedRelay = false;

//Delay time
uint8_t delayTime = 1000;
unsigned long time = 0;

void setup(){ 
  Serial.begin(115200);
  initRF();
  initLED();
  initRelay();
  initButton();
}
 
void loop(){
  loopRF();
}
