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

    private:
        std::shared_ptr<IStorage> storage;
};
#endif