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
    std::optional<SavingAccount> findAccountByAccountNumber(const std::string& account_number);

    bool saveTransaction(const Transaction& transaction);
    std::vector<Transaction> getAllTransactions();
    std::optional<Transaction> findTransactionById(const std::string& transaction_id,
                                                   const std::optional<std::string>& txn_type = std::nullopt);

    bool saveLedger(const Ledger& ledger);
    std::vector<Ledger> loadWholeLedger();

private:
    std::string filename;
    std::mutex fileMutex;

    std::vector<SavingAccount> loadAllAccounts();
    void writeAllAccounts(const std::vector<SavingAccount>& accounts);
    int getNextAccountID(const std::vector<SavingAccount>& accounts);

    std::vector<Transaction> loadAllTransactions();
    void writeAllTransactions(const std::vector<Transaction>& transactions);
    int getNextTransactionID(const std::vector<Transaction>& transactions);


    std::vector<Ledger> loadAllLedger();
    void writeAllLedger(const std::vector<Ledger>& ledgers);
};

#endif