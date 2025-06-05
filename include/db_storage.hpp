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

    std::string getStorageType() const override;

    // User methods
    bool saveUser(const User& user) override;
    bool isUsernameTaken(const std::string& username) override;
    bool isEmailTaken(const std::string& email) override;
    std::optional<User> findUserByUsername(const std::string& username) override;

    // Account methods
    bool saveAccount(const SavingAccount& account) override; //insert into accounts table
    std::optional<SavingAccount> findAccountById(int id) override; // select from accounts
    std::optional<SavingAccount> findAccountByAccountNumber(const std::string& account_number) override;

    // Transaction
    bool saveTransaction(const Transaction& transaction) override;
    std::vector<Transaction> getAllTransactions() override;

    pqxx::connection* getConnection(); // For use in table creation

private:
    
    std::string connectionString;
    bool connected = false;
    std::unique_ptr<pqxx::connection> conn;
};

#endif