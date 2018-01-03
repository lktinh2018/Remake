void initRF() {
  radio.begin();                     
  radio.setAutoAck(1);               
  radio.setRetries(1,1);             
  radio.setDataRate(RF24_1MBPS);      
  radio.setPALevel(RF24_PA_MAX);   
  radio.setChannel(5);
  radio.openWritingPipe(pipe);
}

void loopRF() {
  //Auto send signal to device every delayTime second
  //Send signal "Hello" to device 
  byte x = radio.write(&msgTrans, sizeof(msgTrans));
  Serial.println(x);
  //Check ACK, after failed 3 times relay will deactive
  if(x) {
    count = 0;
    activatedRelay = true;
  } else {
    count++;
    if(count == 3)
      activatedRelay = false;
  }
  delay(3000);
}

