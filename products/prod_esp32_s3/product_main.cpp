#include "data_storer_if/data_storer.hpp"

#include "status_led/status_led.hpp"

#include "product_config.hpp"
#include "wifi_nat_router_app.hpp"
#include "wifi_nat_router_if/wifi_nat_router_factory.hpp"
#include "webserver/webserver.hpp"

#include "freertos/Freertos.h"

static StatusLed::StatusLed * pStatusLed = nullptr;
static WifiNatRouterApp::WifiNatRouterApp * pApp = nullptr;

void product_init(void)
{
    DataStorage::DataStorer::Init();

    if (ENABLE_RGB_LED)
    {
        pStatusLed = new (std::nothrow) StatusLed::StatusLed(RGB_LED_GPIO_PIN);
        assert(pStatusLed);
    }

    pApp = new (std::nothrow) WifiNatRouterApp::WifiNatRouterApp(WifiNatRouter::WifiNatRouterFactory::GetInstance().GetWifiNatRouter(), pStatusLed);
    assert(pApp);
    WebServer & webServer = WebServer::GetInstance();
    webServer.Startup(&(pApp->GetAppIf()));
}

void product_main(void)
{
    for (;;)
    {
        if (pStatusLed)
        {
            pStatusLed->MainLoop();
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}