#ifndef FILE_STORAGE_HPP
#define FILE_STORAGE_HPP

#include "storage.hpp"
#include "csv_storage.hpp"
#include "json_storage.hpp"

class FileStorage : public IStorage {
    CSVStorage csvUsers;
    JSONStorage jsonAccounts;
    JSONStorage jsonTransactions;
    JSONStorage jsonLedger;

    public:
        FileStorage();

        std::string getStorageType() const override;

        // User methods
        bool saveUser(const User& user) override;
        std::optional<User> findUserByUsername(const std::string& username) override;
        bool isUsernameTaken(const std::string& username) override;
        bool isEmailTaken(const std::string& email) override;

        // Account methods
        bool saveAccount(const SavingAccount& account) override;
        std::optional<SavingAccount> findAccountById(int id) override;
        std::optional<SavingAccount> findAccountByAccountNumber(const std::string& account_number) override;

        // Transaction methods
        bool saveTransaction(const Transaction& transaction) override;
        std::vector<Transaction> getAllTransactions() override;
        std::optional<Transaction> findTransactionById(const std::string& transaction_id,
                                                       const std::optional<std::string>& txn_type = std::nullopt) override;

        // Ledger methods
        bool saveLedger(const Ledger& ledger) override;
        std::vector<Ledger> loadWholeLedger() override;
};
#endif