void processControl(int device, int value) {
  if(value) {
    Serial.print("Mở ");
    Serial.println(device);
    digitalWrite(devices[device-1], HIGH);
  }
  else {
    Serial.print("Tắt ");
    Serial.println(device);
    digitalWrite(devices[device-1], LOW);
  }
}

void initControlDevice() {
  for(int i=0; i < numDevice; i++)
    pinMode(devices[i], OUTPUT);
}


