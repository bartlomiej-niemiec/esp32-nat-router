#include "controller.hpp"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "mongoose/mongoose.h"
#include "mongoose/mongoose_glue.h"

#include "esp_log.h"
#include "config.hpp"

void Controller::Startup()
{
    using namespace WifiExtender;

    const AccessPointConfig apConfig(
        DEFAULT_AP_SSID,
        DEFAULT_AP_PASSWORD
    );

    const StaConfig staConfig(
        DEFAULT_STA_SSID,
        DEFAULT_STA_PASSWORD
    );

    auto printApConfig = [](AccessPointConfig ap){
        ESP_LOGI("NvsApConfig", "ssid: %s", ap.ssid.data());
        ESP_LOGI("NvsApConfig", "password: %s", ap.password.data());
    };

    WifiExtenderConfig config(apConfig, staConfig);
    pWifiExtender = &WifiExtenderFactory::GetInstance().GetWifiExtender();
    pWifiScannerIf = pWifiExtender->GetScanner();
   
    if (ESP32S3_TARGET)
    {
        m_Led = new (std::nothrow) NetworkStatusLed::NetworkStatusLed(GPIO_BUILT_RGB_LED_ESP32S3);
    }

    m_WifiExtenderEventQueue = xQueueCreate(WIFI_EXTENDER_QUEUE_SIZE, sizeof(WifiExtender::WifiExtenderState));
    
    assert(nullptr != m_WifiExtenderEventQueue);
    WifiEventDispatcher logEventListener(m_WifiExtenderEventQueue);
    pWifiExtender->RegisterListener(&logEventListener);

    pWifiExtender->Startup(config);
    WebServer & webServerInstance = WebServer::GetInstance();
    webServerInstance.Init(&UserCredential::UserCredentialManager::GetInstance());
    webServerInstance.Startup();
    WifiExtender::WifiExtenderState state;

    while(true)
    {
        if (xQueueReceive(
            m_WifiExtenderEventQueue,
            &state,
            portMAX_DELAY
            ) == pdTRUE )
        {
            m_Led->Update(state);
            if ((state == WifiExtender::WifiExtenderState::CONNECTING ||
                state == WifiExtender::WifiExtenderState::RUNNING))
            {
                
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    };
}