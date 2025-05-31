#include <iostream>
#include "csv_storage.hpp"

CSVStorage::CSVStorage(const std::string& filename) : filename(filename) {}

bool CSVStorage::saveUser(const User& user) {
    std::lock_guard<std::mutex> lock(fileMutex);

    std::vector<User> users = loadUsersFromFileUnlocked();
    cout << "Checking for username\n";
    for (const auto& u : users) {
        if (u.getUsername() == user.getUsername()) {
            std::cerr << "Error: Username '" << user.getUsername() << "' is already taken." << std::endl;
            return false;
        }

        if (u.getEmail() == user.getEmail()) {
            std::cerr << "Error: Email '" << user.getEmail() << "' is already in use." << std::endl;
            return false;
        }
    }
    cout << "Finished check for email.\n";
    cout << "About to create new user\n";
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
            users.emplace_back(User::createUser(firstName, lastName, username, email, password));
        }
    }
    return users;
}

std::vector<User> CSVStorage::loadUsersFromFileUnlocked() {
    std::vector<User> users;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading: " << filename << std::endl;
        return users;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            User user = User::fromCSV(line);
            users.push_back(user);
        }
    }

    file.close();
    return users;
}

void CSVStorage::appendUserToFile(const User& user) {
    cout << "Appending user now.\n";
    std::ifstream infile(filename);
    bool fileExists = infile.good();
    infile.close();

    std::ofstream file(filename, std::ios::app);

    if (!fileExists) {
        file << "FirstName,LastName,Username,Email,Password\n";
    }

    file << user.getFirstName() << ","
         << user.getLastName() << ","
         << user.getUsername() << ","
         << user.getEmail() << ","
         << user.getPassword() << "\n";
}