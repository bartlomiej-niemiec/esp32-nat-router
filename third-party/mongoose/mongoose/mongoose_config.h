#pragma once

#define MG_ARCH MG_ARCH_ESP32
#define MG_ENABLE_CUSTOM_MILLIS 1  // We must implement mg_millis()
#define MG_ENABLE_TCPIP_PRINT_DEBUG_STATS 1  // Enable debug stats log
#define MG_ENABLE_PACKED_FS 1
#define MG_IO_SIZE 1024
#define MG_MAX_HTTP_HEADERS 32

// Uncomment the driver for your device
// #define MG_ENABLE_DRIVER_STM32H 1
// #define MG_ENABLE_DRIVER_STM32F 1
// #define MG_ENABLE_DRIVER_IMXRT 1
// #define MG_ENABLE_DRIVER_SAME54 1
// #define MG_ENABLE_DRIVER_TM4C 1
// #define MG_ENABLE_DRIVER_RA 1
// #define MG_ENABLE_DRIVER_W5500 1
// #define MG_ENABLE_DRIVER_XMC 1
// #define MG_ENABLE_DRIVER_XMC7 1