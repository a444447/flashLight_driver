#ifndef _WIFI_CONTROLLER_H
#define _WIFI_CONTROLLER_H

#include <WiFi.h>
#include <ESPAsyncWebServer.h>

class WiFiControl {
public:
    WiFiControl(const char* ssid, const char* password);
    void begin();
    void handleClient();

private:
    const char* ssid;
    const char* password;
    AsyncWebServer server;
    void setupServer();
};

#endif