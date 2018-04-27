void initIR() {
  debugln("Set Up IR Receiver...");
  irrecv.enableIRIn();
  debugln("Set Up IR Receiver Successful.");
}

void loopIR() {
  if(irrecv.decode(&irResults)) {
    debugHex(irResults.value);
    irrecv.resume();
  }
  delay(100);
}

