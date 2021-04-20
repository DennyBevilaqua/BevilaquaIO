#ifndef LogWebServer_h
#define LogWebServer_h

#include "ESPAsyncWebServer.h"
#include "LogPage.h"

class LogMessageClass
{
private:
    String _msgs[20];
    short size = 0;

public:
    void add(String msg)
    {
        if (size == 20)
        {
            for (short i = size -1; i > 1; i++)
            {
                _msgs[i -1] = _msgs[i];
            }

            size = 19;
        }

        _msgs[size] = msg;
        size++;

        Serial.println(msg);
    }

    String getJson()
    {
        if(size == 0)
            return "";

        String data = "{\"Message\": [";

        for (int i = 0; i < size; i++)
        {
            if (i > 0)
                data += ", ";

            data += "\"" + _msgs[i] + "\"";
        }

        data += "]}";

        return data;
    }

    void clear()
    {
        size = 0;
    }
};

LogMessageClass Log;

class LogWebServerClass
{
private:
    AsyncWebServer *server;
    
    void notFound(AsyncWebServerRequest *request)
    {
        request->send(404, "text/plain", "Not found");
    }

    String getHomeHTML(String page)
    {
        String hostname = WiFi.hostname();
        page.replace("#DEVICE_NAME#", hostname);
        
        return page;
    }

    void home(AsyncWebServerRequest *request)
    {
        request->send(200, "text/html", getHomeHTML(String(LOG_PAGE)));
    }

    void readLog(AsyncWebServerRequest *request)
    {
        String data = Log.getJson();
        request->send(data != "" ? 200 : 204, "application/json", data);
        Log.clear();
    }

public:
    void begin(AsyncWebServer *s)
    {
        server = s;

        server->on("/", HTTP_GET, [&](AsyncWebServerRequest *request) {
            this->home(request);
        });

        server->on("/readLog", HTTP_GET, [&](AsyncWebServerRequest *request) {
            this->readLog(request);
        });

        server->onNotFound([&](AsyncWebServerRequest *request) {
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