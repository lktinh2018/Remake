#include <IRremote.h>

#define DEBUG_MODE

//Config Pin
#define IR_RECEIVER_PIN 2
#define EN_A_PIN        5
#define In1_PIN         6
#define In2_PIN         7
#define EN_B_PIN        8
#define In3_PIN         9
#define In4_PIN         10

//IR
IRrecv irrecv(IR_RECEIVER_PIN);
decode_results irResults;

//Motor
int moveTime = 50;

void debug(String s) {
  #ifdef DEBUG_MODE
    Serial.print(s);
  #endif
}

void debugln(String s) {
  #ifdef DEBUG_MODE
    Serial.println(s);
  #endif
}

void debugHex(int x) {
  #ifdef DEBUG_MODE
    Serial.println(x, HEX);
  #endif
}
