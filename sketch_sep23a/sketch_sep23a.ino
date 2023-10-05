#include <WiFi.h>
#include "config.h"
#include "pwmManager.h"
#include "ledManager.h"
// const char *ssid = "TP-LINK_9682";
// const char *password = "08252234799";

//PWMManager pwmManager(LEDC_TIMER_0, LEDC_CHANNEL_0, GPIO_NUM_18, 5000, LEDC_TIMER_10_BIT); //LEDC_TIMER_10_BIT表示resolution值为10，也就是分为了0~1023
const char* ssid = "TP-LINK_9682";
const char* password = "08252234799";


//QueueHandle_t brightnessQueue;//led亮度控制队列

LED led(2, 0, 5000, 10);


// void LEDControlTask(void*);

void setup() {
  Serial.begin(115200);
  delay(2000);
  led.printPWMInfo();
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
  double brightness = 0.0;
  for (int i = 0; i < 10; i++) {
    led.setBrightness(brightness);
    if (i % 2 == 0) {
      led.printPWMInfo();
    }
    brightness += 10.0;
    delay(500);
  }
}

// void LEDControlTask(void* parameter) {
//     float receivedBrightness;
//     while (true) {
//         if (xQueueReceive(brightnessQueue, &receivedBrightness, portMAX_DELAY)) {
//             led.setBrightness(receivedBrightness);  // 假设led是一个全局的LED对象
//             Serial.println("Brightness set to: " + String(receivedBrightness) + "%");
//         }
//     }
// }