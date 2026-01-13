#pragma once

#include "wifi_nat_router_if.hpp"

namespace WifiNatRouter
{

class WifiNatRouterFactory{

public:

    static const WifiNatRouterFactory & GetInstance();

    WifiNatRouterIf & GetWifiNatRouter() const;

private:

    WifiNatRouterFactory();

};

}