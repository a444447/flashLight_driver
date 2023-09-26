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
}


#endif // _CONFIG_H_