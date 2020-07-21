#include <ESP8266WiFi.h>   
#include "SinricPro.h"
#include "SinricProSwitch.h"
 
#define WIFI_SSID "ID DA REDE"    
#define WIFI_PASS "SENHA DA REDE"
#define APP_KEY "KEY DA API"
#define APP_SECRET "SECRET KEY DA API"
 
#define BomAR_ID "ID DO SWITCH"
#define BomAR D7 //PINO DO GPIO
 
#define BAUD_RATE 9600
 
 
void setupWiFi();
void setupSinricPro();
bool BomARState(const String &deviceId, bool &state); 
 
// main setup function
void setup() {
  Serial.begin(BAUD_RATE); Serial.printf("\r\n\r\n");
  setupWiFi();
  setupSinricPro(); 
  pinMode(BomAR, OUTPUT);
}
 
void loop() {
  SinricPro.handle();
}
 
//Função liga e desliga do motor
bool BomARState(const String &deviceId, bool &state) {
  digitalWrite(BomAR, LOW);
  digitalWrite(BomAR, HIGH);
  delay(1000);
  digitalWrite(BomAR, LOW);
  return true; // request handled properly
}
 
void setupWiFi() {
  Serial.printf("\r\n[Wifi]: Conectando...");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf(".");
    delay(250);
  }
 
  Serial.printf("Conectado!\r\n[WiFi]: Endereço de IP e %s\r\n", WiFi.localIP().toString().c_str());
}
 
// setup das funções para o SinricPro
void setupSinricPro() {
  // add devices and callbacks to SinricPro
  SinricProSwitch &mySwitch1 = SinricPro[BomAR_ID];
  mySwitch1.onPowerState(BomARState);
  
  // setup SinricPro
  SinricPro.onConnected([](){ Serial.printf("Conectado a nuvem SinricPro\r\n"); }); 
  SinricPro.onDisconnected([](){ Serial.printf("Desconectado a nuvem SinricPro\r\n"); });
  SinricPro.begin(APP_KEY, APP_SECRET);
}