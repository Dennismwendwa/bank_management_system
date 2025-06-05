#ifndef STORAGE_HPP
#define STORAGE_HPP
#include <optional>
#include "user.h"
#include "bank_account.h"

class IStorage {
    public:
        virtual ~IStorage() = default;

        virtual std::string getStorageType() const = 0;

        // User methods
        virtual bool saveUser(const User& user) = 0;
        virtual bool isUsernameTaken(const std::string& username) = 0;
        virtual bool isEmailTaken(const std::string& email) = 0;
        virtual std::optional<User> findUserByUsername(const std::string& username) = 0;

        // Account methods
        virtual bool saveAccount(const SavingAccount& account) = 0;
        virtual std::optional<SavingAccount> findAccountById(int id) = 0;
        virtual std::optional<SavingAccount> findAccountByAccountNumber(const std::string& account_number) = 0;

        // Transaction methods
        virtual bool saveTransaction(const Transaction& transaction) = 0;
        virtual std::vector<Transaction> getAllTransactions() = 0;
};
#endif