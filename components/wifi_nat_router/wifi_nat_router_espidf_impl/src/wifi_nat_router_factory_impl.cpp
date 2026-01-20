#include "wifi_nat_router_if/wifi_nat_router_factory.hpp"
#include "wifi_nat_router_if/wifi_nat_router_if.hpp"

#include "wifi_nat_router_impl.hpp"

#include <new>

namespace WifiNatRouter
{

WifiNatRouterFactory::WifiNatRouterFactory()
{
}

const WifiNatRouterFactory & WifiNatRouterFactory::GetInstance()
{
    static const WifiNatRouterFactory factory;
    return factory;
}

WifiNatRouterIf & WifiNatRouterFactory::GetWifiNatRouter() const
{
    static WifiNatRouterImpl * pWifiNatRouterIf = nullptr;
    if (pWifiNatRouterIf == nullptr)
    {
        pWifiNatRouterIf = new (std::nothrow) WifiNatRouterImpl();
        pWifiNatRouterIf->Init();
    }
    assert(pWifiNatRouterIf != nullptr);

    return *pWifiNatRouterIf;
}

}