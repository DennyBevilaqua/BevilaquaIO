#include "LogWebServer.h"

void LogWebServerClass::notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void LogWebServerClass::home(AsyncWebServerRequest *request) {
    request->send(200, "application/json", "{\"id\": \""+_id+"\", \"hardware\": \"ESP8266\"}");
}

void LogWebServerClass::log(String msg) {
}


void LogWebServerClass::begin(AsyncWebServer *s)
{
    server = s;

    server->on("/", HTTP_GET, home);

    server->onNotFound(notFound);
}

void LogWebServerClass::loop(String msg) {
    
}