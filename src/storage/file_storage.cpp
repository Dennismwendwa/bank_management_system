#include "file_storage.hpp"

FileStorage::FileStorage()
    : csvUsers("data/users.csv"),
      jsonAccounts("data/accounts.json"),
      jsonTransactions("data/transactions.json") {}

std::string FileStorage::getStorageType() const {
    return "File";
}

// User methods
bool FileStorage::saveUser(const User& user) {
    return csvUsers.saveUser(user);
}

std::optional<User> FileStorage::findUserByUsername(const std::string& username) {
    return csvUsers.findUserByUsername(username);
}

bool FileStorage::isUsernameTaken(const std::string& username) {
    return csvUsers.isUsernameTaken(username);
}

bool FileStorage::isEmailTaken(const std::string& email) {
    return csvUsers.isEmailTaken(email);
}

// Account methods
bool FileStorage::saveAccount(const SavingAccount& account) {
    return jsonAccounts.saveAccount(account);
}

std::optional<SavingAccount> FileStorage::findAccountById(int id) {
    return jsonAccounts.findAccountById(id);
}

std::optional<SavingAccount> FileStorage::findAccountByAccountNumber(const std::string& account_number) {
    return jsonAccounts.findAccountByAccountNumber(account_number);
}

//Transaction method
bool FileStorage::saveTransaction(const Transaction& transaction) {
    return jsonTransactions.saveTransaction(transaction);
}

std::vector<Transaction> FileStorage::getAllTransactions() {
    return jsonTransactions.getAllTransactions();
}