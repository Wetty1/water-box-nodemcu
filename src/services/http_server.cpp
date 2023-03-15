#include <services/http_server.hpp>
#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

ESP8266WebServer server(80);

extern float aguaEmLitros;
extern int stateSinal;
extern float diffSensorAgua;

void handleRoot()
{
    server.send(200, "text/plain", "hello from esp8266!\r\n");
}

void handleNotFound()
{
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for (uint8_t i = 0; i < server.args(); i++)
    {
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    server.send(404, "text/plain", message);
}

void setupHttpServer()
{
    // CONFIG WEB SERVER
    if (MDNS.begin("esp8266"))
    {
        Serial.println("MDNS responder started");
    }

    server.on("/", handleRoot);

    server.on("/level", []()
              {
              String response = String(aguaEmLitros) + " litros, Distancia: " + String(diffSensorAgua) + ", state: " + String(stateSinal);
              server.send(200, "text/plain", response); });

    server.on("/state", []()
              {
              String response = String(stateSinal);
              server.send(200, "text/plain", response); });

    server.onNotFound(handleNotFound);
    server.begin();
    Serial.println("HTTP server started");
}

void loopHttpServer()
{
    server.handleClient();
    MDNS.update();
}
