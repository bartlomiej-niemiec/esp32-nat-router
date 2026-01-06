#include "network_config_manager.hpp"
#include "config.hpp"

NetworkConfigManager::NetworkConfigManager():
    m_DataStorer(DataStorage::DataStorer::GetInstance())
{
    auto apConfigEntry = m_DataStorer.GetDataEntry<WifiExtender::AccessPointConfig>(m_ApConfigNvsKey);
    if (apConfigEntry.GetData(m_ApConfig) == DataStorage::DataRawStorerIf::ReadStatus::NOT_FOUND)
    {
        const WifiExtender::AccessPointConfig apConfigData(
            DEFAULT_AP_SSID,
            DEFAULT_AP_PASSWORD
        );
        apConfigEntry.SetData(apConfigData);
        apConfigEntry.GetData(m_ApConfig);
    }

    auto staConfigEntry = m_DataStorer.GetDataEntry<WifiExtender::StaConfig>(m_StaConfigNvsKey);
    if (staConfigEntry.GetData(m_StaConfig) == DataStorage::DataRawStorerIf::ReadStatus::NOT_FOUND)
    {
        const WifiExtender::StaConfig staConfigData(
            DEFAULT_STA_SSID,
            DEFAULT_STA_PASSWORD
        );

        staConfigEntry.SetData(staConfigData);
        staConfigEntry.GetData(m_StaConfig);
    }
}   

const WifiExtender::AccessPointConfig & NetworkConfigManager::GetApConfig()
{
    return m_ApConfig;
}   

const WifiExtender::StaConfig & NetworkConfigManager::GetStaConfig()
{
    return m_StaConfig;
}

bool NetworkConfigManager::SetStaConfig(const WifiExtender::StaConfig & staConfig)
{
    auto staConfigEntry = m_DataStorer.GetDataEntry<WifiExtender::StaConfig>(m_StaConfigNvsKey);
    if (staConfigEntry.SetData(staConfig))
    {
        staConfigEntry.GetData(m_StaConfig);
        return true;
    }
    return false;
}

bool NetworkConfigManager::SetApConfig(const WifiExtender::AccessPointConfig & apConfig)
{
    auto apConfigEntry = m_DataStorer.GetDataEntry<WifiExtender::AccessPointConfig>(m_ApConfigNvsKey);
    if (apConfigEntry.SetData(apConfig))
    {
        apConfigEntry.GetData(m_ApConfig);
        return true;
    }
    return false;
}