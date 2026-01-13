#include "wifi_nat_router_app.hpp"

extern "C" void app_main(void)
{
    WifiNatRouter::Init();
    WifiNatRouter::Startup();
}