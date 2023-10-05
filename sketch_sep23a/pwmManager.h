#ifndef _PWM_MANAGER_H
#define _PWM_MANAGER_H

#include "driver/ledc.h"
#include "Arduino.h"

class PWMManager {
public:
    PWMManager(uint8_t pin, uint8_t channel, uint8_t freq, uint8_t resolution);
    ~PWMManager();

    void setDutyCycle(float percentage); //设置亮度，注意是使用的是百分比
    // void setFrequency(uint8_t freq); //设置频率
    // void setDutyResolution(uint resolution); //设置resolution

    void printPWMInfo();

private:
    uint8_t _pin;
    uint8_t _channel;
    uint8_t _freq;
    uint8_t _resolution;


    void init();
};

#endif // _PWM_MANAGER_H
