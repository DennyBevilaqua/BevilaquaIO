#ifndef LogWebServer_h
#define LogWebServer_h

#include "ESPAsyncWebServer.h"

class LogWebServerClass
{
private:
    AsyncWebServer *server;

    void notFound(AsyncWebServerRequest *request)
    {
        request->send(404, "text/plain", "Not found");
    }

    void home(AsyncWebServerRequest *request)
    {
        request->send(200, "application/json", "{\"id\": \"12345\", \"hardware\": \"ESP8266\"}");
    }

public:
    void begin(AsyncWebServer *s)
    {
        server = s;

        server->on("/", HTTP_GET, [&](AsyncWebServerRequest *request){
                this->home(request);
            });

        server->onNotFound([&](AsyncWebServerRequest *request){
                this->notFound(request);
            });
    }

    void log(String msg)
    {
        
    }

    void loop()
    {

    }
};

LogWebServerClass LogWebServer;
#endif