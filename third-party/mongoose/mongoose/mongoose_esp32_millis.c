#include "mongoose.h"
#include <esp_timer.h>

uint64_t mg_millis(void)
{
    return (uint64_t)(esp_timer_get_time() / 1000ULL);
}