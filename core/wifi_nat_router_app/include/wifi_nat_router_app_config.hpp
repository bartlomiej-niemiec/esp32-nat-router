#pragma once

#include <stdint.h>
#include <string_view>


/// Wifi
static constexpr uint8_t ESP_IDF_MINIMAL_PASSWORD_SIZE = 8;

static constexpr std::string_view DEFAULT_AP_SSID = "DEF_AP";
static constexpr std::string_view DEFAULT_AP_PASSWORD = "DEF_AP_PASSWORD";
static constexpr std::string_view DEFAULT_AP_IP_ADDR = "192.168.50.1";
static constexpr std::string_view DEFAULT_AP_NETMASK = "255.255.255.0";

static constexpr std::string_view DEFAULT_STA_SSID = "DEF_STA";
static constexpr std::string_view DEFAULT_STA_PASSWORD = "DEF_STA_PASSWORD";