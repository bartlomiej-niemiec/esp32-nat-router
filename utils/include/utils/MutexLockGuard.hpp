#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

class MutexLockGuard
{
    public:
        explicit MutexLockGuard (SemaphoreHandle_t mutex, TickType_t block_time_tick = portMAX_DELAY);
        bool locked() const { return m_locked; }
        ~MutexLockGuard();
    private:

        MutexLockGuard() = delete;

        SemaphoreHandle_t m_mutex;
        bool m_locked;
};
