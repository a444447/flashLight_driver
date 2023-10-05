#ifndef _LED_MANAGER_H
#define _LED_MANAGER_H

#include "pwmManager.h"
class LED {
public:
    LED(uint8_t pin, uint8_t channel, uint8_t freq, uint8_t resolution);
    ~LED();

    void setBrightness(float percentage);  // 设置LED的亮度，0.0 (完全关闭) 到 100.0 (完全亮)
    
    String getMessage();  // 获取LED的信息

    // void setPWMFrequency(uint32_t freq_hz);
    // void setPWMDutyResolution(ledc_timer_bit_t duty_resolution);
    void printPWMInfo();

private:
    PWMManager pwm;
    String ledMessage;
};

#endif