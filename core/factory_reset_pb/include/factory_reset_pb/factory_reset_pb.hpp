#pragma once

#include <atomic>
#include <stdint.h>
#include "status_led/status_led_if.hpp"
#include "wifi_nat_router_app_if.hpp"
#include "driver/gpio.h"

namespace FactoryReset
{

class FactoryResetPb
{
    public:

        FactoryResetPb(const uint32_t gpio_pin_num,
            StatusLed::StatusLedIf * pStatusLedIf,
            WifiNatRouterApp::WifiNatRouterAppIf * pWifiNatRouterIf
        );

        void MainLoop();

    private:

        const gpio_num_t m_FactoryResetPbGpioPin;
        StatusLed::StatusLedIf * const m_pStatusLedIf;
        WifiNatRouterApp::WifiNatRouterAppIf * const m_pWifiNatRouterIf;

        struct FactoryResetStatus{
            std::atomic<uint32_t> m_FactoryButtonPressed;
            int64_t m_TimeOnPress;
        };

        FactoryResetStatus m_FactoryResetStatus;

        enum class FactoryResetProcessState{
            WAIT,
            PRESSED_FOR_1SEC,
            DONE
        };

        FactoryResetProcessState m_FactoryResetProcessState;

        static void ISR_HANDLER(void *arg);
};

}