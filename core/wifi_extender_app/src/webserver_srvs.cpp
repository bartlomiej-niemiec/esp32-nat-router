#include "webserver_srvs.hpp"

#include "wifi_extender_if/wifi_extender_if.hpp"
#include "wifi_extender_if/wifi_extender_config.hpp"

#include <string_view>

UserCredential::UserCredentialManager * WebServerServices::m_pUserCredentialManager = nullptr;
WifiExtender::WifiExtenderIf * WebServerServices::m_pWifiExtender = nullptr;
NetworkConfigManager * WebServerServices::m_pNetworkConfigManager = nullptr;


void WebServerServices::Init(
                        UserCredential::UserCredentialManager * pUserCredentialManager,
                        WifiExtender::WifiExtenderIf * pWifiExtenderIf,
                        NetworkConfigManager * pNetworkConfigManager
                    )
{
    assert(nullptr != pUserCredentialManager);
    if (m_pUserCredentialManager == nullptr)
    {
        m_pUserCredentialManager = pUserCredentialManager;
    }

    assert(nullptr != pWifiExtenderIf);
    if (m_pWifiExtender == nullptr)
    {
        m_pWifiExtender = pWifiExtenderIf;
    }

    assert(nullptr != pNetworkConfigManager);
    if (m_pNetworkConfigManager == nullptr)
    {
        m_pNetworkConfigManager = pNetworkConfigManager;
    }
}

int WebServerServices::AuthenticateUser(const char *user, const char *pass)
{
    if (!user || !pass) return 0;

    int userlevel = 0;
    std::vector<std::string> users = m_pUserCredentialManager->GetUserNames();
    std::string user_s(user);
    auto it = std::find(users.begin(), users.end(), user_s);
    if (it != users.end())
    {
        auto err = m_pUserCredentialManager->VerifyUserPassword(user, pass, userlevel);
        if (err.has_value())
        {
            userlevel = 0;
        }
    }

    return userlevel;
}


void WebServerServices::GetApSetting(saveapsettings * settings)
{
    WifiExtender::AccessPointConfig apConfig = m_pNetworkConfigManager->GetApConfig();
    strncpy(settings->name, apConfig.ssid.data() ,sizeof(settings->name));
}

void WebServerServices::SetApSetting(saveapsettings * settings)
{

}

void WebServerServices::GetLogin(login * loginData)
{

}

void WebServerServices::SetLogin(login * loginData)
{

}

void WebServerServices::GetStaSettings(savestasettings * settings)
{
    WifiExtender::StaConfig staConfig = m_pNetworkConfigManager->GetStaConfig();
    strncpy(settings->Name, staConfig.ssid.data() ,sizeof(settings->Name));
}

void WebServerServices::SetStaSetings(savestasettings * settings)
{

}

void WebServerServices::GetStaScannedNetworks(stanetworks * networks)
{

}

void WebServerServices::StartStaScannningNetworks(stanetworks * networks)
{

}
        
bool WebServerServices::IsStaScannningComplete(stanetworks * networks)
{
    return true;
}

void WebServerServices::GetWifiExtenderInfo(info * info)
{
    WifiExtender::StaConfig staConfig = m_pNetworkConfigManager->GetStaConfig();
    WifiExtender::AccessPointConfig apConfig = m_pNetworkConfigManager->GetApConfig();
    
    strncpy(info->AP, apConfig.ssid.data() ,sizeof(info->AP));
    strncpy(info->STA, staConfig.ssid.data() ,sizeof(info->STA));

    WifiExtender::WifiExtenderState state = m_pWifiExtender->GetState();
    strncpy(info->State, WifiExtender::WifiExtenderHelpers::WifiExtenderStaToString(state).data(), sizeof(info->State));

    info->Clients = m_pWifiExtender->GetNoClients();
}

void WebServerServices::SetWifiExtenderInfo(info * info)
{

}
        
void WebServerServices::StartSaveEvenet(mg_str params)
{

}

bool WebServerServices::IsSaveEventFinished()
{
    return true;
}