#include <SPI.h>
#include "RF24.h"

//Pin
#define LED_PIN      8

// RF Module
const uint64_t pipe = 0xE8E5F0F0E1LL; 
RF24 radio(9,10);
byte msg[10];

void setup(){
  Serial.begin(115200);
  initRF(); 
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
}
 
void loop(){
  loopRF();
}
