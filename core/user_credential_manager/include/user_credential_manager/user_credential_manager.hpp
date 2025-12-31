#pragma once

#include <string_view>
#include <vector>
#include <optional>
#include "user_credential_manager/user.hpp"

namespace UserCredential
{

class UserCredentialManager
{
    public:

        UserCredentialManager & GetInstance();

        std::vector<std::string_view> GetUserNames() const;

        std::optional<User&> GetUser(std::string_view userName);

        int DeleteUser(std::string_view userName);

        int CreateNewUser(std::string_view userName, std::string_view userPassword, int level = 0);

    private:

        std::vector<User> m_Users;

        UserCredentialManager();

};

}