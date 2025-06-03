#include "bank_ops.hpp"
#include "bank_account.h"

Bank::Bank(std::shared_ptr<IStorage> storage) : storage(std::move(storage)) {
    
}

bool Bank::openAccount(int userId, const std::string& holderName, double initialDeposit, std::string national_id, double interestRate) {
    SavingAccount account = SavingAccount::CreateAccount(userId, holderName, initialDeposit, national_id, interestRate);
    cout << "\n\nNational ID\nid: " << account.getNationalId() << endl;

    if (storage->getStorageType() == "File") {
        
    }
    return storage->saveAccount(account);
}

std::optional<SavingAccount> Bank::getAccountById(int id) {
    return storage->findAccountById(id);
}