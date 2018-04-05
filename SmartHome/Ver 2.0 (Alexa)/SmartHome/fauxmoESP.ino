void initFauxmoESP() {
  fauxmo.enable(true);

  //Add virtual devices
  unsigned char d1 = fauxmo.addDevice("the light");
  unsigned char d2 = fauxmo.addDevice("the mini light");
  unsigned char d3 = fauxmo.addDevice("the fan");
  unsigned char d4 = fauxmo.addDevice("all devices");
  unsigned char d5 = fauxmo.addDevice("the screen backlight");
  fauxmo.onMessage(callback);
}

void loopFauxmoESP() {
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
  } else if(String(deviceName) == "the screen backlight") {
      if(state)
        lcd.backlight();
      else
        lcd.noBacklight();
      return;
  } else if(String(deviceName) == "all devices") {
      digitalWrite(RELAY_PIN_1, state);
      digitalWrite(RELAY_PIN_3, state);
      digitalWrite(RELAY_PIN_4, state);
  
      //LCD
      lcd.clear();
      lcd.print("   All Devices");
      lcd.setCursor(7, 1);
      lcd.print(state ? "On" : "Off");
        
      //Debug
      debugln("");
      debug("All Devices ");
      debug(state ? "ON" : "OFF");
      debugln("");
      return;
  } 
  
  digitalWrite(pinNum, state);

  //Display status
  lcd.clear();
  lcd.print("Device " + String(deviceName));
  lcd.setCursor(7, 1);
  lcd.print(state ? "On" : "Off");
  debugln("");
  debug("Device ");
  debug(deviceName);
  debug(" state ");
  debug(state ? "ON" : "OFF");
  debugln("");
}
