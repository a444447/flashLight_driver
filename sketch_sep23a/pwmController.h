#ifndef _PWMCONTROLLER_H_
#define _PWMCONTROLLER_H_
#include <vector>
#include <map>
#include "Arduino.h"

struct pwmProperty
{
    /* data */
    uint8_t pin{0}; //引脚
    uint8_t duty{0}; //占空比
    uint8_t freq{0}; //频率
    uint8_t channel{0}; //通道
    uint8_t resolution{0}; //分辨率, 假如resolution=8, 则占空比的范围为0~255，也就是将占空比分为256份
    //bool isEnable; 是否启用
    bool isAttach{false}; //pin是否注册了pwm
};

class pwmController
{
public:
    //构造函数
    pwmController(const std::vector<uint8_t> &pins) {
            for (auto pin : pins) {
            pwmProperty pwm;
            pwm.pin = pin;
            pwmProperties[pin] = pwm;
        }
    }
    void init();
    //查看当前引脚的状态
    void pwm_pin_status();
    //为指定引脚设置占空比
    void pwm_set_duty(uint8_t pin, uint8_t duty);
    void pwm_set_duty(uint8_t duty);
    //为指定注册的引脚设置频率
    void pwm_set_freq(uint8_t pin, uint8_t freq);
    void pwm_set_freq(uint8_t freq);
    //为指定注册的引脚设置分辨率
    void pwm_set_resolution(uint8_t pin, uint8_t resolution);
    void pwm_set_resolution(uint8_t resolution);
    //为指定注册的引脚设置通道
    void pwm_set_channel(uint8_t pin, uint8_t channel);
    void pwm_set_channel(uint8_t channel);

private:
   std::map<uint8_t, pwmProperty> pwmProperties; 
};


#endif