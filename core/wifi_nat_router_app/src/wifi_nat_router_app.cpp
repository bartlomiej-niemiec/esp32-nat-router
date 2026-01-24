#include "wifi_nat_router_app.hpp"
#include "wifi_nat_router_app_impl.hpp"

#include "wifi_nat_router_if/wifi_nat_router_factory.hpp"

namespace WifiNatRouterApp
{

WifiNatRouterApp::WifiNatRouterApp(WifiNatRouter::WifiNatRouterIf & rWifiIf, StatusLed::StatusLed * pStatusLed):
    m_pWifiNatRouterAppImpl(nullptr)
{
    m_pWifiNatRouterAppImpl = new (std::nothrow) WifiNatRouterAppImpl(rWifiIf, pStatusLed);
    assert(nullptr != m_pWifiNatRouterAppImpl);
}

WifiNatRouterApp::~WifiNatRouterApp()
{
    delete m_pWifiNatRouterAppImpl;
}

WifiNatRouterAppIf & WifiNatRouterApp::GetAppIf() const
{
    return *m_pWifiNatRouterAppImpl;
}

}