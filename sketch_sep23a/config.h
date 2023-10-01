#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <map>
#include <string>
#include <vector>

namespace flashLight_driver {

    //wifi配置
    static std::map<std::string, std::string> wifi_config {
        {"ssid", "Xiaomi-bx53"},
        {"password", "08252234799"}
    };
    //设置可用引脚集合
    static std::map<std::string, std::vector<uint8_t>> led_pins {
        {"PIN_VEC", {4, 14, 27, 16}}
    };
}


#endif // _CONFIG_H_