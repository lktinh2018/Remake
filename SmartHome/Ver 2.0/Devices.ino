void initDevices() {
  pinMode(RELAY_PIN_1, OUTPUT);
  pinMode(RELAY_PIN_2, OUTPUT);
  pinMode(RELAY_PIN_3, OUTPUT);
  pinMode(RELAY_PIN_4, OUTPUT);
  fauxmo.enable(true);

  // Add virtual devices
  unsigned char d1 = fauxmo.addDevice("the light");
  unsigned char d2 = fauxmo.addDevice("the mini light");
  unsigned char d3 = fauxmo.addDevice("the fan");
  unsigned char d4 = fauxmo.addDevice("all devices");
  fauxmo.onMessage(callback);
}

void loopDevices() {
  fauxmo.handle();
}

void callback(uint8_t deviceID, const char * deviceName, bool state) {
  int pinNum;
  if(String(deviceName) == "the light") {
    pinNum = RELAY_PIN_1;
  } else if(String(deviceName) == "the mini light") {
    pinNum = RELAY_PIN_3;
  } else if(String(deviceName) == "the fan") {
    pinNum = RELAY_PIN_4;
  } else if(String(deviceName) == "all devices") {
    digitalWrite(RELAY_PIN_1, state);
    digitalWrite(RELAY_PIN_3, state);
    digitalWrite(RELAY_PIN_4, state);
    return;
  } 
  lcd.clear();
  lcd.print("Device " + String(deviceName));
  lcd.setCursor(7, 1);
  lcd.print(state ? "On" : "Off");
  Serial.println();
  Serial.print("Device ");
  Serial.print(deviceName);
  Serial.print(" state ");
  Serial.print(state ? "ON" : "OFF");
  Serial.println();
  digitalWrite(pinNum, state);
}
