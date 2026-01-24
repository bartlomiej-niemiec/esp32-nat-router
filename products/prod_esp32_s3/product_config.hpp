#pragma once

#include <stdint.h>
#include <string_view>

/// RGB Status LED
static constexpr bool ENABLE_RGB_LED = true;
static constexpr uint32_t GPIO_BUILT_RGB_LED_ESP32S3 = 38;
static constexpr uint32_t RGB_LED_GPIO_PIN = GPIO_BUILT_RGB_LED_ESP32S3;