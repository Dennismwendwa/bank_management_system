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

    bool saveTransaction(const Transaction& transaction);
    std::vector<Transaction> getAllTransactions();

private:
    std::string filename;
    std::mutex fileMutex;

    std::vector<SavingAccount> loadAllAccounts();
    void writeAllAccounts(const std::vector<SavingAccount>& accounts);
    int getNextAccountID(const std::vector<SavingAccount>& accounts);

    std::vector<Transaction> loadAllTransactions();
    void writeAllTransactions(const std::vector<Transaction>& transactions);
    int getNextTransactionID(const std::vector<Transaction>& transactions);
};

#endif