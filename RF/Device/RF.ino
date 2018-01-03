void initRF() {
  radio.begin();                     
  radio.setAutoAck(1);              
  radio.setDataRate(RF24_1MBPS);
  radio.setChannel(40);
  radio.openReadingPipe(1, pipe);     
  radio.startListening();         
}

void loopRF() {
  if (radio.available()){
    while (radio.available()){
      radio.read(&msg, sizeof(msg));
      String message = String((char*)msg);
      Serial.println(message);
      if(message == "Hello") {
        for(int i = 1; i<=10; i++) {
          digitalWrite(LED_PIN, LOW);
          delay(200);
          digitalWrite(LED_PIN, HIGH);
          delay(200);
        }
      }
    }
  }
}

