#include "freertos/FreeRTOS.h"

#include "wifi_extender_if/wifi_extender_config.hpp"
#include "wifi_extender_if/wifi_extender_factory.hpp"
#include "wifi_extender_if/wifi_extender_if.hpp"
#include "wifi_extender_if/wifi_extender_scanner_types.hpp"

#include "rgbled_if/rgbled_if.hpp"
#include "rgbled_if/rgbled_factory.hpp"
#include "rgbled_if/rgbled_utils.hpp"

#include "data_storer_if/data_storer.hpp"

#include "mongoose_glue.h"
#include "esp_log.h"

#include "config.hpp"
#include <string>


static volatile bool isMongooseRunning = false;
static constexpr char m_pTaskName[] = "MongooseWebServer";
static constexpr int MONGOOSE_TASK_STACK_SIZE = 4096 * 2;
static constexpr int MONGOOSE_TASK_PRIO = 3;
static TaskHandle_t m_MongooseTaskHandle = nullptr;

static void run_mongoose(void *pArg) {
    ESP_LOGI("MONGOOSE", "run_mongoose started");
    mongoose_init();
    mg_log_set(MG_LL_DEBUG);  // Set log level to debug
    for (;;) {                // Infinite event loop
        mongoose_poll();   // Process network events
    }
}

class LogEventListener:
    public WifiExtender::EventListener
{
    public:

        void Callback(WifiExtender::WifiExtenderState event) override
        {
            ESP_LOGI("WifiExtender", "State: %s", WifiExtender::WifiExtenderHelpers::WifiExtenderStaToString(event).data());
            if ((event == WifiExtender::WifiExtenderState::CONNECTING ||
                event == WifiExtender::WifiExtenderState::RUNNING) && !isMongooseRunning)
            {
                xTaskCreate(
                    run_mongoose,
                    m_pTaskName,
                    MONGOOSE_TASK_STACK_SIZE,
                    nullptr,
                    MONGOOSE_TASK_PRIO,
                    &m_MongooseTaskHandle
                );
                assert(nullptr != m_MongooseTaskHandle);
                isMongooseRunning = true;
            }
        }
};


extern "C" void app_main(void)
{
    using namespace WifiExtender;

    DataStorage::DataStorer::Init();

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

    DataStorage::DataStorer & dataStorer = DataStorage::DataStorer::GetInstance();
    std::string_view ap_conifg_key = "apconfig";
    AccessPointConfig nvsApConfig{};
    DataStorage::DataEntry<AccessPointConfig> apConfigEntry = dataStorer.GetDataEntry<AccessPointConfig>(ap_conifg_key);
    DataStorage::DataRawStorerIf::ReadStatus status = apConfigEntry.GetData(nvsApConfig);
    if (status == DataStorage::DataRawStorerIf::ReadStatus::NOK)
    {
        apConfigEntry.Remove();
    }

    apConfigEntry.SetData(apConfig);
    apConfigEntry.GetData(nvsApConfig);

    printApConfig(nvsApConfig);

    WifiExtenderConfig config(apConfig, staConfig);
    WifiExtenderIf & rWifiExtender = WifiExtenderFactory::GetInstance().GetWifiExtender();
    WifiExtenderScannerIf * pScanner = rWifiExtender.GetScanner();
    pScanner->RegisterStateListener([pScanner](ScannerState state){
        if (state == ScannerState::Done)
        {
            const std::vector<WifiNetwork> & networks = pScanner->GetResults();
            for (const WifiNetwork & n : networks)
            {
                printNetwork(n);
            }
        }
    });
    assert(nullptr != pScanner);
    static LogEventListener listener;
    rWifiExtender.RegisterListener(&listener);
    rWifiExtender.Startup(config);
    while(true)
    {
        vTaskDelay(pdMS_TO_TICKS(1500));
    };
}