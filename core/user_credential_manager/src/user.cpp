#include "user_credential_manager/user.hpp"
#include <data_storer_if/data_storer.hpp>

namespace UserCredential
{

User::User(std::string_view name, std::string_view password, int level)
{
    Data tempData{};
    auto & dataStorer = DataStorage::DataStorer::GetInstance();
    auto dataEntry = dataStorer.GetDataEntry<Data>(name);



}

User::~User()
{

}

bool User::ChangePassword(std::string_view newPassword)
{
    return false;
}

bool User::ChangeLevel(const int newLevel)
{
    return false;
}

bool User::VerifyPassword(std::string_view password)
{
    return false;
}


}

