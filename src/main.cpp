#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <DNSServer.h>
#include <sensors/readable_distance.hpp>
#include <services/http_server.hpp>
#include <services/http_api_client.hpp>
#include <services/Wifi_service.hpp>
#include <utils/ota_service.hpp>
#include <services/change_state_sinal.hpp>
#include <global_variables.hpp>

#define pinTrigger D1
#define pinEcho D0

extern float diffSensorAgua;
extern int stateSinal;

void setup()
{
  delay(2000);
  Serial.begin(115200);
  Serial.println("[Setup]");
  delay(2000);

  setupHttpServer();
  setupOtaService();
  pinMode(LED_BUILTIN, OUTPUT); // Initialize the LED_BUILTIN pin as an output
  sonarBegin(pinTrigger, pinEcho);
  setupWifi();
  stateSinal = getCurrentState();
}

// the loop function runs over and over again forever
void loop()
{
  diffSensorAgua = calcularDistancia();
  checkStateSinal();
  loopHttpServer();
  otaLoopHandle();
}
