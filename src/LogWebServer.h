#include "ESPAsyncWebServer.h"

class LogWebServerClass
{
    private:
        AsyncWebServer *server;
        void notFound(AsyncWebServerRequest *request);
        home(AsyncWebServerRequest *request);
    
    public:
        void begin(AsyncWebServer *s);
        void log(String msg);
        void loop();
};

LogWebServerClass LogWebServer;