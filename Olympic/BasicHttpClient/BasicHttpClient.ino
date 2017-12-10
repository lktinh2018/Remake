#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

String currentFirmware = "4.5.6";

void setup() {
  USE_SERIAL.begin(115200);
  USE_SERIAL.println();

  WiFiMulti.addAP("TanHoangLong_L6", "saigon135");
  delay(3000);
}

void loop() {
  String respone = HTTPRequest("http://192.168.60.180/checkfirmware");
  if(respone == "ERROR") {
    Serial.println("Error Request");
  } else {
    String newFirmware = respone;
    if(checkCurrentFirmware(newFirmware))
      updateFirmware();
    else
      Serial.println("You're last version");
  }

  delay(10000);
}



