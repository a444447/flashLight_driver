#include "WiFiControl.h"
#include "LED.h"  // 引入你的LED类

extern LED led;  // 假设你在主程序中已经定义了一个LED对象

WiFiControl::WiFiControl(const char* ssid, const char* password)
    : ssid(ssid), password(password), server(6789)  // HTTP通常使用端口80
{}

void WiFiControl::begin() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    setupServer();
    server.begin();
}

void WiFiControl::handleClient() {
    // 在loop()函数中调用，处理客户端请求
}

void WiFiControl::setupServer() {
    server.on("/setBrightness", HTTP_GET, [](AsyncWebServerRequest* request) {
    if (request->hasParam("value")) {
        String value = request->getParam("value")->value();
        float brightness = value.toFloat();

        // 发送亮度值到队列
        xQueueSend(brightnessQueue, &brightness, portMAX_DELAY);
        
        request->send(200, "text/plain", "Brightness set request received.");
    } else {
        request->send(400, "text/plain", "Value parameter missing");
    }
    });
}