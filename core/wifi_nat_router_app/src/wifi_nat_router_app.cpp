#include "wifi_nat_router_app.hpp"

#include "wifi_nat_router_if/wifi_nat_router_config.hpp"
#include "wifi_nat_router_if/wifi_nat_router_factory.hpp"
#include "wifi_nat_router_if/wifi_nat_router_if.hpp"
#include "wifi_nat_router_if/wifi_scanner_scanner_types.hpp"

#include "user_credential_manager/user_credential_manager.hpp"

#include "network_config_manager.hpp"
#include "network_status_led.hpp"

#include "webserver.hpp"
#include "webserver_srvs.hpp"

#include "mongoose/mongoose.h"
#include "mongoose/mongoose_glue.h"

#include "esp_log.h"
#include "config.hpp"

#include "wifi_event_monitor.hpp"

#include "data_storer_if/data_storer.hpp"

namespace WifiNatRouter
{

void Init()
{
    DataStorage::DataStorer::Init();
}

void Startup()
{
    NetworkConfigManager m_NetworkConfigManager;

    WifiNatRouter::
WifiNatRouterIf & rWifiNatRouter = WifiNatRouter::
WifiNatRouterFactory::GetInstance().GetWifiNatRouter();

    NetworkStatusLed::NetworkStatusLed * m_Led = nullptr;
    WifiEventMonitor wifiEventMonitor;
    if (ESP32S3_TARGET)
    {
        m_Led = new (std::nothrow) NetworkStatusLed::NetworkStatusLed(GPIO_BUILT_RGB_LED_ESP32S3);
        wifiEventMonitor.Subscribe([&m_Led](WifiNatRouter::
WifiNatRouterState state){m_Led->Update(state);});
        wifiEventMonitor.Startup();
    }
    
    rWifiNatRouter.Startup({m_NetworkConfigManager.GetApConfig(), m_NetworkConfigManager.GetStaConfig()});

    constexpr uint32_t DELAY_MS = 200;
    vTaskDelay(pdMS_TO_TICKS(DELAY_MS));

    WebServerServices::Init(
        &(UserCredential::UserCredentialManager::GetInstance()),
        &rWifiNatRouter,
        &m_NetworkConfigManager,
        &wifiEventMonitor
    );
    
    WebServer & webServerInstance = WebServer::GetInstance();
    webServerInstance.Startup();

    for (;;)
    {
        vTaskDelay(pdTICKS_TO_MS(2000));
    }
}


}