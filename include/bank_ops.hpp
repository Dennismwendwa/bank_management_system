#ifndef BANK_OPS_HPP
#define bACK_OPS_HPP

#include <string>
#include <memory>
#include "storage.hpp"

class Bank {

    public:
        Bank(std::shared_ptr<IStorage> storage);

        bool openAccount(int userId, const std::string& holderName, double initialDeposit, std::string national_id, double interestRate);
        std::optional<SavingAccount> getAccountById(int id);
        bool withdraw(std::string account_number, double amount);
        bool deposit(std::string account_number, std::string id_number, double amount);
        bool transfer(std::string id_number, std::string from_account_number, std::string to_account_number, double amount);

        void recordTransaction(const std::string& type, const SavingAccount& account, double amount, const std::string& description);
        void recordTransaction(std::string transaction_id, const std::string& type, const SavingAccount& account, double amount, const std::string& description,
                               const SavingAccount& from_account);
                               
        void saveUpdatedAccount(const SavingAccount& account);

    private:
        std::shared_ptr<IStorage> storage;
};
#endif