#ifndef JSON_STORAGE_HPP
#define JSON_STORAGE_HPP

#include <string>
#include <mutex>
#include <optional>
#include "bank_account.h"

class JSONStorage {
public:
    explicit JSONStorage(const std::string& filename);

    bool saveAccount(const SavingAccount& account);
    std::optional<SavingAccount> findAccountById(int id);

private:
    std::string filename;
    std::mutex fileMutex;

    std::vector<SavingAccount> loadAllAccounts();
    void writeAllAccounts(const std::vector<SavingAccount>& accounts);
    int getNextAccountID(const std::vector<SavingAccount>& accounts);
};

#endif