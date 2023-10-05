#include "pwmManager.h"

static const char *TAG = "PWMManager";  // 用于ESP_LOG的标签

PWMManager::PWMManager(ledc_timer_t timer, ledc_channel_t channel, gpio_num_t gpio, uint32_t freq_hz, ledc_timer_bit_t duty_resolution, ledc_mode_t speed_mode) 
    : m_timer(timer), m_channel(channel), m_gpio(gpio), m_freq_hz(freq_hz), m_duty_resolution(duty_resolution), m_speed_mode(speed_mode) {
    init();
}

PWMManager::~PWMManager() {
    // TODO 析构代码，例如停止PWM或者释放资源等
}

void PWMManager::init() {
    ledc_timer_config_t ledc_timer = {
        .speed_mode = m_speed_mode,
        .duty_resolution = m_duty_resolution,
        .timer_num = m_timer,
        .freq_hz = m_freq_hz,
    };
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel;
    ledc_channel.speed_mode = m_speed_mode;
    ledc_channel.channel = m_channel;
    ledc_channel.timer_sel = m_timer;
    ledc_channel.gpio_num = m_gpio;
    ledc_channel.duty = 0;
    ledc_channel_config(&ledc_channel);
}

void PWMManager::setDutyCycle(float percentage) {
    if (percentage < 0) percentage = 0;
    if (percentage > 100) percentage = 100;

    uint32_t max_duty = (1 << m_duty_resolution) - 1; // 根据占空比解析度计算
    uint32_t duty = (percentage / 100.0) * max_duty;

    ledc_set_duty(m_speed_mode, m_channel, duty);
    ledc_update_duty(m_speed_mode, m_channel);
}

void PWMManager::setFrequency(uint32_t freq_hz) {
    m_freq_hz = freq_hz;
    ledc_set_freq(m_speed_mode, m_timer, m_freq_hz);
}

void PWMManager::setDutyResolution(ledc_timer_bit_t duty_resolution) {
    m_duty_resolution = duty_resolution;
    init();  // 重新初始化，因为改变了占空比解析度
}

void PWMManager::printPWMInfo() {
    Serial.println("------ PWM Information ------");
    Serial.print("GPIO: ");
    Serial.println(m_gpio);
    Serial.print("Timer: ");
    Serial.println(m_timer);
    Serial.print("Channel: ");
    Serial.println(m_channel);
    Serial.print("Frequency: ");
    Serial.print(m_freq_hz);
    Serial.println(" Hz");
    Serial.print("Duty Resolution: ");
    Serial.print(m_duty_resolution);
    Serial.println("-bit");
    Serial.print("Speed Mode: ");
    Serial.println(m_speed_mode == LEDC_HIGH_SPEED_MODE ? "High Speed" : "Low Speed");

    uint32_t max_duty = (1 << m_duty_resolution) - 1;
    uint32_t current_duty = ledc_get_duty(m_speed_mode, m_channel);
    float percentage = (float)current_duty / max_duty * 100.0;

    Serial.print("Current Duty Cycle: ");
    Serial.print(percentage);
    Serial.println("%");
}
