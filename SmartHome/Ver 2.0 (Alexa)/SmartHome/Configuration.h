#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include "fauxmoESP.h"
#include <TimeLib.h>
#include <Ticker.h>

//Debug mode
#define DEBUG_MODE

//Config wifi
#define SSID      "Quach Tai"
#define PASSWORD  "quachtai"

//Config devices pin
#define RELAY_PIN_1 12
#define RELAY_PIN_2 14
#define RELAY_PIN_3 13
#define RELAY_PIN_4 15

//LCD (Change Wire.begin() to Wire.begin(2, 0) in lib)
LiquidCrystal_I2C lcd(0x27, 16, 2);
byte degree[8] = {0B01110, 0B01010, 0B01110, 0B00000, 0B00000, 0B00000, 0B00000, 0B00000};

//DHT
#define DHTPIN 10
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int t, h;

//fauxoESP  instance
fauxmoESP fauxmo;

// NTP Config
static const char ntpServerName[] = "0.asia.pool.ntp.org";
//Timezone
const int timeZone = 7;

WiFiUDP Udp;
unsigned int localPort = 8888;

time_t getNtpTime();
void digitalClockDisplay();
void printDigits(int digits);
void sendNTPpacket(IPAddress &address);

//Web Updater
const char* update_path = "/";
const char* update_username = "raimht93";
const char* update_password = "77778888@";

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;

//Ticker
Ticker printToLCD;

void debug(String s) {
  #ifdef DEBUG_MODE
    Serial.print(s);
  #endif
}

void debugln(String s) {
  #ifdef DEBUG_MODE
    Serial.println(s);
  #endif
}
