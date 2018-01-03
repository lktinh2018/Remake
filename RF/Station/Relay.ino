void initRelay() {
  pinMode(RELAY_PIN, OUTPUT);
  deactiveRelay() ;
}

void activeRelay() {
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(LED_PIN, HIGH);
}

void deactiveRelay() {
 digitalWrite(RELAY_PIN, HIGH);
 digitalWrite(LED_PIN, LOW);
}

