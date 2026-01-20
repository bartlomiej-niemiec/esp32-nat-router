#include "utils/MutexLockGuard.hpp"
#include "assert.h"

MutexLockGuard::MutexLockGuard (SemaphoreHandle_t mutex, TickType_t block_time_tick):
    m_mutex(mutex),
    m_locked(false)
{
    assert(nullptr != mutex);
    m_locked = xSemaphoreTake(m_mutex, block_time_tick) == pdTRUE;
}

MutexLockGuard::~MutexLockGuard()
{
    if (m_locked)
    {
        xSemaphoreGive(m_mutex);
    }
}