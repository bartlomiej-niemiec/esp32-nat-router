#include "wifi_extender_app.hpp"
#include "controller.hpp"

#include "data_storer_if/data_storer.hpp"

namespace WifiExtenderApp
{

void Init()
{
    DataStorage::DataStorer::Init();
}

void Startup()
{
    static Controller controller;
    controller.Startup();
}


}