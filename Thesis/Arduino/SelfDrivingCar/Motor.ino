void initMotor() {
  debugln("Set Up Motor...");
  pinMode(EN_A_PIN, OUTPUT);
  pinMode(EN_B_PIN, OUTPUT);
  pinMode(In1_PIN,  OUTPUT);
  pinMode(In2_PIN,  OUTPUT);
  pinMode(In3_PIN,  OUTPUT);
  pinMode(In4_PIN,  OUTPUT);
  debugln("Set Up Motor Successful.");
}

void loopMotor() {
  digitalWrite(EN_A_PIN, HIGH);
  digitalWrite(EN_B_PIN, LOW);
  digitalWrite(In1_PIN, HIGH);
  digitalWrite(In2_PIN, LOW);
  digitalWrite(In3_PIN, HIGH);
  digitalWrite(In4_PIN, LOW);
  delay(10000);
  digitalWrite(In1_PIN, LOW);
  digitalWrite(In2_PIN, HIGH);
  digitalWrite(In3_PIN, LOW);
  digitalWrite(In4_PIN, HIGH);
  delay(10000);
}

void moveLeft() {
  
}

void moveRight() {
  digitalWrite(In1_PIN, HIGH);
  digitalWrite(In2_PIN, LOW);
  digitalWrite(In3_PIN, HIGH);
  digitalWrite(In4_PIN, LOW);
  delay(10000);
}

void moveFoward() {
  
}

void moveReverse() {
  
}

