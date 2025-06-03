#include <iostream>
#include "db_storage.hpp"


DatabaseStorage::DatabaseStorage(const std::string& connStr)
    : connectionString(connStr), connected(false) {}

bool DatabaseStorage::connect() {
    try {
        conn = std::make_unique<pqxx::connection>(connectionString);
        if (conn->is_open()) {
            connected = true;
        }
    } catch (const std::exception& e) {
        std::cerr << "DB Connection failed: " << e.what() << std::endl;
        connected = false;
    }
    return connected;
}

bool DatabaseStorage::isConnected() const {
    return connected;
}

std::string DatabaseStorage::getStorageType() const {
    return "Database";
}

pqxx::connection* DatabaseStorage::getConnection() {
    return conn.get();
}

bool DatabaseStorage::saveUser(const User& user) {
    try {
        pqxx::work txn(*conn);
        txn.exec_params(
            "INSERT INTO users (first_name, last_name, username, email, password) "
            "VALUES ($1, $2, $3, $4, $5)",
            user.getFirstName(),
            user.getLastName(),
            user.getUsername(),
            user.getEmail(),
            user.getPassword()
        );
        txn.commit();
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error saving user: " << e.what() << std::endl;
        return false;
    }
}

bool DatabaseStorage::isUsernameTaken(const std::string& username) {
    try {
        pqxx::work txn(*conn);
        pqxx::result result = txn.exec_params(
            "SELECT 1 FROM users WHERE username = $1 LIMIT 1",
            username
        );
        return !result.empty();
    } catch (const std::exception& e) {
        std::cerr << "Error checking username: " << e.what() << std::endl;
        return false;
    }
}

bool DatabaseStorage::isEmailTaken(const std::string& email) {
    try {
        pqxx::work txn(*conn);
        pqxx::result result = txn.exec_params(
            "SELECT 1 FROM users WHERE email = $1 LIMIT 1",
            email
        );
        return !result.empty();
    } catch (const std::exception& e) {
        std::cerr << "Error checking email: " << e.what() << std::endl;
        return false;
    }
}

std::optional<User> DatabaseStorage::findUserByUsername(const std::string& username) {
    try {
        pqxx::work txn(*conn);
        pqxx::result result = txn.exec_params(
            "SELECT first_name, last_name, username, email, password "
            "FROM users WHERE username = $1 LIMIT 1",
            username
        );

        if (!result.empty()) {
            const auto& row = result[0];
            return User::createUser(
                row["first_name"].c_str(),
                row["last_name"].c_str(),
                row["username"].c_str(),
                row["email"].c_str(),
                row["password"].c_str()
            );
        }

        return std::nullopt;
    } catch (const std::exception& e) {
        std::cerr << "Error finding user: " << e.what() << std::endl;
        return std::nullopt;
    }
}

bool DatabaseStorage::saveAccount(const SavingAccount& account) {
    // For later
    cout << account.getAccountId() << endl;
    std::cout << "[DB] Saving account (stub)\n";
    return true;
}

std::optional<SavingAccount> DatabaseStorage::findAccountById(int id) {
    // for later
    cout << id << endl;
    std::cout << "[DB] Finding account by ID (stub)\n";
    return std::nullopt;
}