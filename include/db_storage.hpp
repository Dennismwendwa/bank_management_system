#ifndef DB_STORAGE_HPP
#define DB_STORAGE_HPP

#include <memory>
#include <pqxx/pqxx>
#include "storage.hpp"
//#include "user.hpp"

class DatabaseStorage : public IStorage {
public:
    explicit DatabaseStorage(const std::string& connStr);

    bool connect();
    bool isConnected() const;

    bool saveUser(const User& user) override;
    bool isUsernameTaken(const std::string& username) override;
    bool isEmailTaken(const std::string& email) override;
    std::optional<User> findUserByUsername(const std::string& username) override;

    pqxx::connection* getConnection(); // For use in table creation

private:
    
    std::string connectionString;
    bool connected = false;
    std::unique_ptr<pqxx::connection> conn;
};

#endif