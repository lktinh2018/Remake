#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "Timer.h"
#include "WorkScheduler.h"
#include "DHT.h"

//Config network
const char* ssid      = "LKT";
const char* password  = "77778888@";
const char* broker    = "192.168.137.1";

//Client
WiFiClient espClient;
PubSubClient client(espClient);
DynamicJsonBuffer jsonBuffer;
char msg[100];
int value = 0;

//Devices
int numDevice = 4;
int devices[] = {12, 14, 13, 15};

//LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);
byte degree[8] = {0B01110,0B01010,0B01110,0B00000,0B00000,0B00000,0B00000,0B00000};

//RTC
const byte DS1307 = 0x68;
const byte NumberOfFields = 7;
int second, minute, hour, day, wday, month, year;

//DHT
#define DHTPIN 10
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int t, h;

//PIR
#define PIRPIN 9999

//Buzzer
#define BUZZERPIN 3

//Timer
WorkScheduler *printToLCD;

void setup() {
  Serial.begin(115200);
  initBuzzer();
  initLCD();
  initRTC();
  initDHT();
  initTimer();
  initClient();
  initControlDevice();
}

void loop() {
  loopClient();
  loopTimer();
}







