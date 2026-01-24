#include "data_storer_if/data_storer.hpp"

#include "status_led/status_led.hpp"

#include "product_config.hpp"
#include "wifi_nat_router_app.hpp"
#include "wifi_nat_router_if/wifi_nat_router_factory.hpp"
#include "webserver/webserver.hpp"

#include "freertos/Freertos.h"

void product_main(void)
{
    DataStorage::DataStorer::Init();

    StatusLed::StatusLed * pStatusLed = nullptr;
    if (ENABLE_RGB_LED)
    {
        pStatusLed = new (std::nothrow) StatusLed::StatusLed(RGB_LED_GPIO_PIN);
    }

    WifiNatRouterApp::WifiNatRouterApp app(WifiNatRouter::WifiNatRouterFactory::GetInstance().GetWifiNatRouter(), pStatusLed);
    WebServer & webServer = WebServer::GetInstance();
    webServer.Startup(&app.GetAppIf());

    for (;;)
    {
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}