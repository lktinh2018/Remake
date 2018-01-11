#include <ESP8266WiFi.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include "Timer.h"
#include "WorkScheduler.h"
#include "fauxmoESP.h"
#include <WiFiUdp.h>
#include <TimeLib.h>

#define DEBUG_MODE 

//Config wifi
#define SSID      "LKT"
#define PASSWORD  "77778888@"

//Control devices
#define RELAY_PIN_1 12
#define RELAY_PIN_2 14
#define RELAY_PIN_3 13
#define RELAY_PIN_4 15

fauxmoESP fauxmo;

//LCD (Change Wire.begin() to Wire.begin(2, 0) in lib)
LiquidCrystal_I2C lcd(0x27, 16, 2);
byte degree[8] = {0B01110,0B01010,0B01110,0B00000,0B00000,0B00000,0B00000,0B00000};

//RTC
//const byte DS1307 = 0x68;
//const byte NumberOfFields = 7;
//int second, minute, hour, day, wday, month, year;

//DHT
#define DHTPIN 10
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int t, h;

//Timer
WorkScheduler *printToLCD;

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

void setup() {
  #ifdef DEBUG_MODE
    Serial.begin(115200);
    Serial.println();
  #endif
  initLCD();
  initWiFi();
  initNTP();
  initDevices();
  
//  initRTC();
//  initDHT();
  initTimer();
}

void loop() {
  loopTimer();
  loopDevices();
}

void initWiFi() {
    WiFi.mode(WIFI_STA);
    Serial.printf("[WIFI] Connecting to %s ", SSID);
    WiFi.begin(SSID, PASSWORD);
    lcd.clear();
    lcd.print("  Connecting");
    lcd.setCursor(4, 1);
    lcd.print("To WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }
    Serial.println();
    Serial.println("Connected to wifi");
    lcd.clear();
    lcd.print("   Connected");
    lcd.setCursor(4, 1);
    lcd.print("To WiFi");
}

void debug(String s) {
  #ifdef DEBUG_MODE
    Serial.println(s);
  #endif
}

