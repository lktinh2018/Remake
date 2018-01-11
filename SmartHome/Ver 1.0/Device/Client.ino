void initClient() {
  setUpWifi();
  client.setServer(broker, 8883);
  client.setCallback(callback);
}

void loopClient() {
  if (!client.connected())
    reconnect();
  client.loop();
  
//  ++value;
//  snprintf (msg, 75, "Hello World #%ld", value);
//  Serial.print("Publish message: ");
//  Serial.println(msg);
//  client.publish("outTopic", msg);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.println();
  String data;
  for (int i = 0; i < length; i++)
    data += (char)payload[i];
  processData(data);

}

void processData(String data) {
  JsonObject& root = jsonBuffer.parseObject(data);
  String event = root["event"];
  if(event == "CONTROL")
    processControl(root["device"], root["value"]);
}

void setUpWifi() {
  delay(10);
  Serial.print("\nConnecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  lcd.clear();
  lcd.print(" Connecting  to");
  lcd.setCursor(7, 1);
  lcd.print("wifi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  
  Serial.println("\nWiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    lcd.clear();
    lcd.print(" Connecting");
    lcd.setCursor(0,1);
    lcd.print("   to broker");
    if (client.connect("ESP8266-Node")) {
      Serial.println("\nConnected to broker");
      char macAddress[20];
      String(WiFi.macAddress()).toCharArray(macAddress, 20);
      client.subscribe(macAddress);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("Try again in 3 seconds");
      delay(3000);
    }
  }
}
