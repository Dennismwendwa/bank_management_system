#ifndef STORAGE_HPP
#define STORAGE_HPP
#include <optional>
#include "user.h"

class IStorage {
    public:
        virtual ~IStorage() = default;

        virtual bool saveUser(const User& user) = 0;
        virtual bool isUsernameTaken(const std::string& username) = 0;
        virtual bool isEmailTaken(const std::string& email) = 0;
        virtual std::optional<User> findUserByUsername(const std::string& username) = 0;
};
#endif