#pragma once

#include "wifi_nat_router_if/wifi_nat_router_config.hpp"
#include "data_storer_if/data_storer.hpp"

class NetworkConfigManager
{
    public:

        NetworkConfigManager();

        const WifiNatRouter::
AccessPointConfig & GetApConfig();

        const WifiNatRouter::
StaConfig & GetStaConfig();

        bool SetStaConfig(const WifiNatRouter::
StaConfig & staConfig);

        bool SetApConfig(const WifiNatRouter::
AccessPointConfig & staConfig);

    private:

        WifiNatRouter::
AccessPointConfig m_ApConfig;
        WifiNatRouter::
StaConfig m_StaConfig;

        static constexpr std::string_view m_ApConfigNvsKey  = "ApConfig";
        static constexpr std::string_view m_StaConfigNvsKey = "StaConfig";

        DataStorage::DataStorer & m_DataStorer;
};