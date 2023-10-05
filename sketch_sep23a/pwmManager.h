#ifndef _PWM_MANAGER_H
#define _PWM_MANAGER_H

#include "driver/ledc.h"
#include "Arduino.h"

class PWMManager {
public:
    PWMManager(ledc_timer_t timer, ledc_channel_t channel, gpio_num_t gpio, uint32_t freq_hz, ledc_timer_bit_t duty_resolution, ledc_mode_t speed_mode = LEDC_HIGH_SPEED_MODE);
    ~PWMManager();

    void setDutyCycle(float percentage); //设置亮度，注意是使用的是百分比
    void setFrequency(uint32_t freq_hz); //设置频率
    void setDutyResolution(ledc_timer_bit_t duty_resolution); //设置resolution

    void printPWMInfo();

private:
    ledc_timer_t m_timer;
    ledc_channel_t m_channel;
    gpio_num_t m_gpio;
    uint32_t m_freq_hz;
    ledc_timer_bit_t m_duty_resolution;
    ledc_mode_t m_speed_mode;

    void init();
};

#endif // _PWM_MANAGER_H
