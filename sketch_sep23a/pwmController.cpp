#include "pwmController.h"

void pwmController::init(uint8_t freq, uint8_t resolution) {
    uint8_t channel{0};
    for (auto &pair : pwmProperties) {
        pwmProperty &pwm = pair.second;
        pwm.freq = freq;
        pwm.resolution = resolution;
        if (!pwm.isAttach) {
            ledcSetup(pwm.channel, freq, resolution);
            ledcAttachPin(pwm.pin, channel);
            pwm.isAttach = true;
            pwm.channel = channel;
        }
        channel++;
    }
}

void pwmController::pwm_pin_status() {
    Serial.println("PWM Pin Status:");
    for (const auto &pair : pwmProperties) {
        const pwmProperty &pwm = pair.second;
        Serial.print("Pin: ");
        Serial.print(pwm.pin);
        Serial.print(", Duty: ");
        Serial.print(pwm.duty);
        Serial.print(", Freq: ");
        Serial.print(pwm.freq);
        Serial.print(", Channel: ");
        Serial.print(pwm.channel);
        Serial.print(", Resolution: ");
        Serial.print(pwm.resolution);
        Serial.print(", Is Attached: ");
        Serial.println(pwm.isAttach ? "Yes" : "No");
    }
}

// 为指定引脚设置占空比
void pwmController::pwm_set_duty(uint8_t pin, uint8_t duty) {
    if (pwmProperties.find(pin) != pwmProperties.end()) {
        pwmProperties[pin].duty = duty;
        ledcWrite(pwmProperties[pin].channel, duty);
    }
}

// 为所有引脚设置占空比
void pwmController::pwm_set_duty(uint8_t duty) {
    for (auto &pair : pwmProperties) {
        pwmProperty &pwm = pair.second;
        pwm.duty = duty;
        ledcWrite(pwm.channel, duty);
    }
}



// 为指定引脚设置频率
void pwmController::pwm_set_freq(uint8_t pin, uint8_t freq) {
    if (pwmProperties.find(pin) != pwmProperties.end()) {
        pwmProperties[pin].freq = freq;
        ledcWriteTone(pwmProperties[pin].channel, freq);
    }
}

// 为所有引脚设置频率
void pwmController::pwm_set_freq(uint8_t freq) {
    for (auto &pair : pwmProperties) {
        pwmProperty &pwm = pair.second;
        pwm.freq = freq;
        ledcWriteTone(pwm.channel, freq);
    }
}

void pwmController::pwm_set_resolution(uint8_t pin, uint8_t resolution) {
    if (pwmProperties.find(pin) != pwmProperties.end()) {
        pwmProperties[pin].resolution = resolution;
        ledcSetup(pwmProperties[pin].channel, pwmProperties[pin].freq, resolution);
    }
}

// 为所有引脚设置分辨率
void pwmController::pwm_set_resolution(uint8_t resolution) {
    for (auto &pair : pwmProperties) {
        pwmProperty &pwm = pair.second;
        pwm.resolution = resolution;
        ledcSetup(pwm.channel, pwm.freq, resolution);
    }
}

// 为指定引脚设置通道
void pwmController::pwm_set_channel(uint8_t pin, uint8_t channel) {
    if (pwmProperties.find(pin) != pwmProperties.end()) {
        pwmProperties[pin].channel = channel;
        ledcDetachPin(pwmProperties[pin].pin);
        ledcAttachPin(pwmProperties[pin].pin, channel);
    }
}

// 为所有引脚设置通道
void pwmController::pwm_set_channel(uint8_t channel) {
    for (auto &pair : pwmProperties) {
        pwmProperty &pwm = pair.second;
        pwm.channel = channel;
        ledcDetachPin(pwm.pin);
        ledcAttachPin(pwm.pin, channel);
    }
}