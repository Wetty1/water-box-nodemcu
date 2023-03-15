#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <env.hpp>
#include <string>

WiFiClient client;
HTTPClient http;
extern char *url_api;

bool sendChangeSinal(float distance, float litros, int sinal)
{

    Serial.print("[HTTP] begin...\n");
    // configure traged server and url
    http.begin(client, url_api); // HTTP
    http.addHeader("Content-Type", "application/json");

    Serial.print("[HTTP] POST...\n");
    // start connection and send HTTP header and body
    int httpCode = http.POST("{\"literage\": " + String(litros) + ", \"sinal\": " + String(sinal) + "}");

    // httpCode will be negative on error
    if (httpCode > 0)
    {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] POST... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK)
        {
            const String &payload = http.getString();
            Serial.println("received payload:\n<<");
            Serial.println(payload);
            Serial.println(">>");
        }
    }
    else
    {
        Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
    if (httpCode < 300)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int getCurrentState()
{
    int response = 2;
    Serial.print("[HTTP] begin...\n");
    // configure traged server and url
    http.begin(client, "http://192.168.100.71:3000/water-box"); // HTTP
    // http.addHeader("Content-Type", "application/json");

    Serial.print("[HTTP] GET...\n");
    // start connection and send HTTP header and body
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0)
    {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK)
        {
            const String &payload = http.getString();
            Serial.println("received payload:\n<<");
            Serial.println(payload);
            Serial.println(">>");
            response = payload.toInt();
        }
    }
    else
    {
        Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();

    return response;
}