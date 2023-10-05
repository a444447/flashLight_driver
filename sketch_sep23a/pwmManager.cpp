#include "pwmManager.h"

static const char *TAG = "PWMManager";  // 用于ESP_LOG的标签

PWMManager::PWMManager(uint8_t pin, uint8_t channel, uint8_t freq, uint8_t resolution) 
    : _pin(pin), _channel(channel), _freq(freq), _resolution(resolution) {
    init();
}

PWMManager::~PWMManager() {
    // TODO 析构代码，例如停止PWM或者释放资源等
}

void PWMManager::init() {
    ledcSetup(_channel, _freq, _resolution);
    ledcAttachPin(_pin, _channel);
}

void PWMManager::setDutyCycle(float percentage) {
    if (percentage < 0) percentage = 0;
    if (percentage > 100) percentage = 100;

    uint32_t max_duty = (1 << _resolution) - 1; // 根据占空比解析度计算
    uint32_t duty = (percentage / 100.0) * max_duty;

    ledcWrite(_channel, duty);
}

// void PWMManager::setFrequency(uint32_t freq_hz) {
    
// }

// void PWMManager::setDutyResolution(ledc_timer_bit_t duty_resolution) {
//     m_duty_resolution = duty_resolution;
//     init();  // 重新初始化，因为改变了占空比解析度
// }

void PWMManager::printPWMInfo() {
    Serial.println("------ PWM Information ------");
    Serial.print("GPIO: ");
    Serial.println(_pin);
    Serial.print("Channel: ");
    Serial.println(_channel);
    Serial.print("Frequency: ");
    Serial.print(_freq);
    Serial.println(" Hz");
    Serial.print("Duty Resolution: ");
    Serial.print(_resolution);
    Serial.println("-bit");
    
    uint32_t max_duty = (1 << _resolution) - 1;
    uint32_t current_duty = ledcRead(_channel);
    Serial.print("current_duty:");
    Serial.println(current_duty);
    float percentage = (float)current_duty / max_duty * 100.0;

    Serial.print("Current Duty Cycle: ");
    Serial.print(percentage);
    Serial.println("%");
}
