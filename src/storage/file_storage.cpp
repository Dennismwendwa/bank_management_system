#include "file_storage.hpp"

FileStorage::FileStorage()
    : csvUsers("files/users.csv"), jsonAccounts("files/accounts.json") {}

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