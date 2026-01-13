#include "wifi_event_monitor.hpp"
#include "wifi_nat_router_if/wifi_nat_router_factory.hpp"

#include "esp_log.h"

#include <new>

WifiEventMonitor::WifiEventMonitor():
    m_WifiEventDispatcher(nullptr),
    m_WifiNatRouterEventQueue(nullptr),
    m_WifiMonitoraskHandle(nullptr)
{
    m_WifiNatRouterEventQueue = xQueueCreate(WIFI_NAT_ROUTER_QUEUE_SIZE, sizeof(WifiNatRouter::
WifiNatRouterState));
    assert(nullptr != m_WifiNatRouterEventQueue);
    m_WifiEventDispatcher = new (std::nothrow) WifiEventDispatcher(m_WifiNatRouterEventQueue);
    assert(nullptr != m_WifiEventDispatcher);
}

WifiEventMonitor::~WifiEventMonitor()
{
    delete m_WifiEventDispatcher;
    vQueueDelete(m_WifiNatRouterEventQueue);
}

bool WifiEventMonitor::Subscribe(const ListenerFunction & function)
{
    m_Listeners.push_back(function);
    return true;
}

bool WifiEventMonitor::Startup()
{
    if (m_WifiMonitoraskHandle != nullptr) return false;

    WifiNatRouter::
WifiNatRouterIf & pWifiNatRouter = WifiNatRouter::
WifiNatRouterFactory::GetInstance().GetWifiNatRouter();
    xTaskCreate(
        WifiMonitorObserverTask,
        m_pTaskName.data(),
        TASK_STACK_SIZE,
        this,
        TASK_PRIO,
        &m_WifiMonitoraskHandle
    );
    assert(nullptr != m_WifiMonitoraskHandle);
    pWifiNatRouter.RegisterListener(m_WifiEventDispatcher);

    return true;
}

void WifiEventMonitor::WifiMonitorObserverTask(void *pArg)
{
    assert(nullptr != pArg);
    WifiEventMonitor * pInstance = reinterpret_cast<WifiEventMonitor *>(pArg);
    WifiNatRouter::
WifiNatRouterState state;
    while (1)
    {
        if (xQueueReceive(
            pInstance->m_WifiNatRouterEventQueue,
            &state,
            portMAX_DELAY
            ) == pdTRUE )
        {
            for (auto & subcriber : pInstance->m_Listeners)
            {
                subcriber(state);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}