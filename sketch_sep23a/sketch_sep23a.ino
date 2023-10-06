#include <WiFi.h>
#include "config.h"
#include "pwmManager.h"
#include "ledManager.h"

const char* ssid = "Xiaomi-bx53";
const char* password = "08252234799";

WiFiServer server(4789);

void wifi_task(void*);
void led_task(void*);


//消息队列，控制led与wifi任务之间的消息传递。 
QueueHandle_t wifi_led_handler;
LED led(2, 0, 5000, 10); //GPIO2作为测试


// void LEDControlTask(void*);

void setup() {
  Serial.begin(115200);
  delay(2000);
  led.printPWMInfo();

  // WiFi.begin(flashLight_driver::wifi_config["ssid"].c_str(), flashLight_driver::wifi_config["password"].c_str());
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected!");
  Serial.println("IP address:");
  Serial.println(WiFi.localIP());

  //消息队列初始化
  wifi_led_handler = xQueueCreate(10, sizeof(double));


  server.begin();

  xTaskCreate(
    wifi_task,
    "WiFiTask",
    2048,
    NULL,
    2,
    NULL
  );
  xTaskCreate(
    led_task,
    "LedTask",
    4096,
    NULL,
    2,
    NULL
  );
//   xTaskCreate(
//     LEDControlTask,   // 任务函数
//     "LEDControl",     // 任务名称
//     2000,             // 栈大小
//     NULL,             // 任务参数
//     2,                // 任务优先级
//     NULL              // 任务句柄（如果你不需要使用它，可以设置为NULL）
// );
}

void loop() {

}

void led_task(void* parameters) {
  Serial.println("led task running...");
  double percentage;
  while(1) {
    int ret = xQueueReceive(wifi_led_handler, &percentage,  portMAX_DELAY);
    if (ret == pdPASS) {
      Serial.print("成功设置亮度:");
      Serial.println(percentage);
      led.setBrightness(percentage);
    } else {
      Serial.println("xQueueReceive fail.");
    }
  }
}

void wifi_task(void* parameters) {
  uint8_t buffer[32];
  Serial.println("wifi task running...");
  while(1) {
    // 检查是否有客户端尝试连接
    WiFiClient client = server.available();
    if (client) {
      Serial.println("Client connected!");
      while(client.connected()) {
        if (client.available()) {
          int length = client.read(buffer, sizeof(buffer) - 1);
          if (length > 0) {
            buffer[length] = '\0';
            double percentage = atof((const char*)buffer);
            int ret = xQueueSend(wifi_led_handler, (void*) &percentage, 0);
            if (ret == pdTRUE) {
              Serial.print("成功加入队列:");
              Serial.println(percentage);
            }
          }
        }
        client.println("received!");
      }
      client.stop();
      Serial.println("Client disconnected");
    }
  }
}