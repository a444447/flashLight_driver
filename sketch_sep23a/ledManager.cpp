#include "ledManager.h"

LED::LED(ledc_timer_t timer, ledc_channel_t channel, gpio_num_t gpio)
    : pwm(timer, channel, gpio, 5000, LEDC_TIMER_10_BIT)  // 假设默认使用5kHz频率和10-bit占空比解析度
{
    ledMessage = "LED Initialized.";
}

LED::~LED() {
    // 你可以在这里添加析构函数的内容，如果需要的话
}

void LED::setBrightness(float percentage) {
    pwm.setDutyCycle(percentage);
    ledMessage = "LED brightness set to " + String(percentage) + "%";
}

String LED::getMessage() {
    return ledMessage;
}

void LED::setPWMFrequency(uint32_t freq_hz) {
    pwm.setFrequency(freq_hz);  // 调用PWMManager的setFrequency函数
    ledMessage = "PWM frequency set to " + String(freq_hz) + " Hz";
}

void LED::setPWMDutyResolution(ledc_timer_bit_t duty_resolution) {
    pwm.setDutyResolution(duty_resolution);  // 调用PWMManager的setDutyResolution函数
    ledMessage = "PWM duty resolution set to " + String(duty_resolution) + "-bit";
}