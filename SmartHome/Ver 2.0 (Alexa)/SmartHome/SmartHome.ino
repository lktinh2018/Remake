#include "Configuration.h"

void setup() {
  #ifdef DEBUG_MODE
    Serial.begin(115200);
    Serial.println();
  #endif
  initDevices();
  initDHT();
  initLCD();
  initWiFi();
  initNTP();
  initTimer();
  initFauxmoESP();
  initWebUpdater();
}

void loop() {
  loopTimer();
  loopFauxmoESP();
  loopWebUpdater();
}

void initWiFi() {
  WiFi.mode(WIFI_STA);
  debug("Connecting to ");
  debugln(SSID);
  WiFi.begin(SSID, PASSWORD);
  lcd.clear();
  lcd.print("  Connecting");
  lcd.setCursor(4, 1);
  lcd.print("To WiFi");
  while(WiFi.status() != WL_CONNECTED) {
    debug(".");
    delay(100);
  }
  debugln("");
  debugln("Connected to wifi");
  lcd.clear();
  lcd.print("   Connected");
  lcd.setCursor(4, 1);
  lcd.print("To WiFi");
}



