#pragma once

#include "network_config_manager.hpp"
#include "user_credential_manager/user_credential_manager.hpp"
#include "wifi_extender_if/wifi_extender_if.hpp"

#include "mongoose/mongoose_glue.h"

class WebServerServices
{

    public:

        static void Init(UserCredential::UserCredentialManager * pUserCredentialManager,
                        WifiExtender::WifiExtenderIf * pWifiExtenderIf,
                        NetworkConfigManager * pNetworkConfigManager);

        static int AuthenticateUser(const char *user, const char *pass);
        
        static void GetApSetting(saveapsettings * settings);

        static void SetApSetting(saveapsettings * settings);

        static void GetLogin(login * loginData);

        static void SetLogin(login * loginData);

        static void GetStaSettings(savestasettings * settings);

        static void SetStaSetings(savestasettings * settings);

        static void GetStaScannedNetworks(stanetworks * networks);

        static void StartStaScannningNetworks(stanetworks * networks);
        
        static bool IsStaScannningComplete(stanetworks * networks);

        static void GetWifiExtenderInfo(info * info);

        static void SetWifiExtenderInfo(info * info);
        
        static void StartSaveEvenet(mg_str params);

        static bool IsSaveEventFinished();
        

    private:

        static UserCredential::UserCredentialManager * m_pUserCredentialManager;

        static WifiExtender::WifiExtenderIf * m_pWifiExtender;

        static NetworkConfigManager * m_pNetworkConfigManager;

};