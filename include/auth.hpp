#ifndef AUTH_HPP
#define AUTH_HPP

#include <string>
#include <memory>
#include "storage.hpp"

class Auth {

    public:
        Auth(std::shared_ptr<IStorage> storage);
        bool registerUser(
                        const std::string& firstName,
                        const std::string& lastName,
                        const std::string& username,
                        const std::string& email,
                        const std::string& password);
        bool login(const std::string& username, const std::string& password);

    private:
        std::shared_ptr<IStorage> storage;
};

#endif