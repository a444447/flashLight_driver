#ifndef _LED_MANAGER_H
#define _LED_MANAGER_H

#include "pwmManager.h"
class LED {
public:
    LED(ledc_timer_t timer, ledc_channel_t channel, gpio_num_t gpio);
    ~LED();

    void setBrightness(float percentage);  // 设置LED的亮度，0.0 (完全关闭) 到 100.0 (完全亮)
    
    String getMessage();  // 获取LED的信息

    void setPWMFrequency(uint32_t freq_hz);
    void setPWMDutyResolution(ledc_timer_bit_t duty_resolution);

private:
    PWMManager pwm;
    String ledMessage;
};

#endif