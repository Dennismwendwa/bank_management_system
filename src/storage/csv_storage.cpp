#include <iostream>
#include "csv_storage.hpp"

CSVStorage::CSVStorage(const std::string& filename) : filename(filename) {}

bool CSVStorage::saveUser(const User& user) {
    std::lock_guard<std::mutex> lock(fileMutex);

    if (isUsernameTaken(user.getUsername())) {
        std::cerr << "Error: Username '" << user.getUsername();
        std::cerr << "' is already taken." << std::endl;
        return false;
    }

    if (isEmailTaken(user.getEmail())) {
        std::cerr << "Error: Email '" << user.getEmail();
        std::cerr << "' is already in use." << std::endl;
        return false;
    }

    appendUserToFile(user);
    return true;
}

bool CSVStorage::isUsernameTaken(const std::string& username) {
    auto users = loadAllUsers();
    for (const auto& u : users) {
        if (u.getUsername() == username) return true;
    }
    return false;
}

bool CSVStorage::isEmailTaken(const std::string& email) {
    auto users = loadAllUsers();
    for (const auto& u : users) {
        if (u.getEmail() == email) return true;
    }
    return false;
}

std::optional<User> CSVStorage::findUserByUsername(const std::string& username) {
    auto users = loadAllUsers();
    for (const auto& u : users) {
        if (u.getUsername() == username) {
            return u;
        }
    }
    return std::nullopt;
}

std::vector<User> CSVStorage::loadAllUsers() {
    std::lock_guard<std::mutex> lock(fileMutex);

    std::vector<User> users;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string firstName, lastName, username, email, password;

        std::getline(ss, firstName, ',');
        std::getline(ss, lastName, ',');
        std::getline(ss, username, ',');
        std::getline(ss, email, ',');
        std::getline(ss, password, ',');

        if (!username.empty()) {
            //users.emplace_back(firstName, lastName, username, email, password);
            users.emplace_back(User::createUser(firstName, lastName, username, email, password));
        }
    }
    return users;
}

void CSVStorage::appendUserToFile(const User& user) {
    std::ofstream file(filename, std::ios::app);
    file << user.getFirstName() << ","
         << user.getLastName() << ","
         << user.getUsername() << ","
         << user.getEmail() << ","
         << user.getPassword() << "\n";
}