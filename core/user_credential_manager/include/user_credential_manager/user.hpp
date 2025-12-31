#pragma once

#include <string_view>
#include <stdint.h>
#include <data_storer_if/data_entry.hpp>

#include <algorithm>
#include <cstring>

namespace UserCredential
{

static constexpr uint32_t MAX_USERNAME_SIZE = 32;
static constexpr uint32_t MAX_PASSWORD_SIZE = 64;

class User{

    public:

        User(std::string_view name, std::string_view password, int level = 0);

        User(std::string_view name);

        ~User();

        bool ChangePassword(std::string_view newPassword);

        bool ChangeLevel(const int newLevel);

        bool VerifyPassword(std::string_view password);

    private:

        struct Data{
            char name[MAX_USERNAME_SIZE];
            char password[MAX_PASSWORD_SIZE];
            int level;

            Data() = default;

            Data(std::string_view name, std::string_view password, int level)
            {
                size_t min = MAX_USERNAME_SIZE - 1 < name.size() ? name.size() : MAX_USERNAME_SIZE - 1;
                strncpy(this->name, name.data(), min);
                this->name[min + 1] = '\0';

                min = MAX_PASSWORD_SIZE - 1 < password.size() ? password.size() : MAX_PASSWORD_SIZE - 1;
                strncpy(this->password, password.data(), min);
                this->password[min + 1] = '\0';

                this->level = level;
            }


            Data & operator=(Data & data){
                size_t min = MAX_USERNAME_SIZE - 1 < strnlen(data.name, MAX_USERNAME_SIZE) ? strnlen(data.name, MAX_USERNAME_SIZE) : MAX_USERNAME_SIZE - 1;
                strncpy(this->name, data.name, min);
                name[min + 1] = '\0';

                min = MAX_PASSWORD_SIZE - 1 < strnlen(data.password, MAX_USERNAME_SIZE) ? strnlen(data.password, MAX_USERNAME_SIZE): MAX_PASSWORD_SIZE - 1;
                strncpy(this->password, data.password, min);
                password[min + 1] = '\0';

                this->level = data.level;

                return *this;
            }

        };
        
        Data m_CachedData;

};

}

