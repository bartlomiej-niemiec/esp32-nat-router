#pragma once 

#include "ping/ping_sock.h"
#include "esp_log.h"
#include  <functional>

class InternetAccessChecker
{
    public:

        using InternetAccessCallback = std::function<void(bool IsInternetAccess)>;

        InternetAccessChecker(const InternetAccessCallback & cb);

        ~InternetAccessChecker();

        bool Check();

    private:

        esp_ping_handle_t m_InternetAccessPingHandle;

        InternetAccessCallback m_Cb;

        bool m_runnning;

        int m_ping_timeout_count;

        int m_ping_success_count;

        static void on_ping_success_cb(esp_ping_handle_t hdl, void *args)
        {
            auto * pInstance = reinterpret_cast<InternetAccessChecker*>(args);
            pInstance->m_ping_success_count++;
        }

        static void on_ping_timeout_cb(esp_ping_handle_t hdl, void *args)
        {
            auto * pInstance = reinterpret_cast<InternetAccessChecker*>(args);
            pInstance->m_ping_timeout_count++;
        }

        static void on_ping_end_cb(esp_ping_handle_t hdl, void *args)
        {
            auto * pInstance = reinterpret_cast<InternetAccessChecker*>(args);
            ESP_LOGI("InternetAccessChecker", "Ping Success Count: %i, Ping Timeout Count: %i", pInstance->m_ping_success_count, pInstance->m_ping_timeout_count);
            pInstance->m_Cb(pInstance->m_ping_success_count > 0);
            pInstance->m_runnning = false;
        }

};