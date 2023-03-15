#include <services/Wifi_service.hpp>
#include <Arduino.h>
#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "****"
#define STAPSK "****"
#endif

const char *ssid = STASSID;
const char *password = STAPSK;

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 100, 201);

void setupWifi()
{
    WiFi.mode(WIFI_STA);
    WiFi.config(apIP, IPAddress(192, 168, 100, 1), IPAddress(255, 255, 255, 0));
    WiFi.begin(ssid, password);

    Serial.println("");

    while (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.println("Connection Failed! Rebooting...");
        delay(5000);
        ESP.restart();
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    Serial.println("WIFI Ready");
}
