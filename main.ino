#ifdef ENABLE_DEBUG
 #define DEBUG_ESP_PORT Serial
 #define NODEBUG_WEBSOCKETS
 #define NDEBUG
#endif

#include <Arduino.h>
#ifdef ESP8266
 #include <ESP8266WiFi.h>
#endif
#ifdef ESP32
 #include <WiFi.h>
#endif


#include <SinricPro.h>
#include "Cafeteira.h"

/*********************************
*Dados fornecidos pelo Sirinc Pro  *
**********************************/

#define APP_KEY    "fd32af5d-6c44-4ed6-8XXXXXXXXXXXXXXXX" //Aba Credenciais
#define APP_SECRET "13470948-938d-4af3-9b84-fcab3f0534d5-f5cf3921-c2e1-45f8-aXXXXXXXXXXXXXXXX"  //Aba Credenciais
#define DEVICE_ID  "683f7944929fca43024abc57" //Aba Dispositivos

/****************
* Dados do WI-FI *
*****************/

#define SSID       "USAR SEU WIFI"
#define PASS       "SENHA DO SEU WIFI"

/***********************************************************
* Config de velocidade da Serial e Pinos de Entrada e Saída *
************************************************************/
#define BAUD_RATE  115200
#define relay_out  25
#define sens_cof   34


/*************************************
* Parâmetros do controle de temperatura *
**************************************/

#define TEMP_ALVO 100.0  // Temperatura considerada "café pronto" (ajuste conforme necessário)
#define TEMP_MARGEM 5.0   // Margem para evitar oscilação
#define INTERVALO_LEITURA 5000 // Intervalo entre leituras (ms)


Cafeteira &cafeteira = SinricPro[DEVICE_ID];


/*******************
* Variáveis globais *
*******************/

bool globalPowerState = false;
bool cafePronto = false;
unsigned long ultimaLeitura = 0;


/*************
* Callbacks *
*************/

bool onPowerState(const String &deviceId, bool &state) {
 Serial.printf("[Device: %s]: Powerstate changed to %s\r\n", deviceId.c_str(), state ? "on" : "off");
 globalPowerState = state;
 digitalWrite(relay_out, globalPowerState ? HIGH : LOW);
  if (globalPowerState) {
   cafePronto = false; // Reseta o estado quando liga a cafeteira
 }
  return true;
}


/*********************
* Funções Auxiliares *
*********************/


float lerTemperatura() {
 int leitura_NTC = analogRead(sens_cof);
 // Esta é uma conversão simplificada - você deve calibrar para seu sensor específico
 float temperatura = map(leitura_NTC, 0, 4095, 0, 120); // Convertendo para graus Celsius
 Serial.printf("Leitura NTC: %d, Temperatura: %.1f°C\n", leitura_NTC, temperatura);
 return temperatura;
}


void verificarTemperatura() {
 float temperatura = lerTemperatura();
  // Se atingiu a temperatura alvo e ainda não marcou como pronto
 if (temperatura >= TEMP_ALVO && !cafePronto) {
   cafePronto = true;
   Serial.println("Café pronto! Desligando cafeteira...");
  
   // Desliga a cafeteira
   globalPowerState = false;
   digitalWrite(relay_out, LOW);
  
   // Atualiza o estado no SinricPro
   cafeteira.sendPowerStateEvent(false);
 }
}


/********
* Setup *
********/


void setupSinricPro() {
 cafeteira.onPowerState(onPowerState);
 SinricPro.onConnected([]{ Serial.printf("[SinricPro]: Connected\r\n"); });
 SinricPro.onDisconnected([]{ Serial.printf("[SinricPro]: Disconnected\r\n"); });
 SinricPro.begin(APP_KEY, APP_SECRET);
}


void setupWiFi() {
 #if defined(ESP8266)
   WiFi.setSleepMode(WIFI_NONE_SLEEP);
   WiFi.setAutoReconnect(true);
 #elif defined(ESP32)
   WiFi.setSleep(false);
   WiFi.setAutoReconnect(true);
 #endif


 WiFi.begin(SSID, PASS);
 Serial.printf("[WiFi]: Connecting to %s", SSID);
 while (WiFi.status() != WL_CONNECTED) {
   Serial.printf(".");
   delay(250);
 }
 Serial.printf("connected\r\n");
}


void setup() {
 Serial.begin(BAUD_RATE);
  // Inicializa os pinos
 pinMode(relay_out, OUTPUT);
 pinMode(sens_cof, INPUT);
 digitalWrite(relay_out, LOW); // Inicia com relé desligado
  setupWiFi();
 setupSinricPro();
}


/*******
* Loop *
*******/


void loop() {
 SinricPro.handle();
  // Verifica a temperatura periodicamente se a cafeteira estiver ligada
 if (globalPowerState && !cafePronto && millis() - ultimaLeitura >= INTERVALO_LEITURA) {
   verificarTemperatura();
   ultimaLeitura = millis();
 }
}
