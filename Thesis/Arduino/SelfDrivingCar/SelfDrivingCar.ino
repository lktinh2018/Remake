#include "Configuration.h"

void setup() {
  #ifdef DEBUG_MODE
    Serial.begin(115200);
  #endif
//  initIR();
  initMotor();
}

void loop() {
//  loopIR();
  loopMotor();

}
