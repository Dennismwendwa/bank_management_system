#include <iostream>
#include "csv_storage.hpp"

CSVStorage::CSVStorage(const std::string& filename) : filename(filename) {}

bool CSVStorage::saveUser(const User& user) {
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
        cout << "\nuser: " << u.getUsername() << endl;
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
        std::string idStr, firstName, lastName, username, email, password;

        std::getline(ss, idStr, ',');
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
    std::ifstream infile(filename);
    bool fileExists = infile.good();
    infile.close();

    std::ofstream file(filename, std::ios::app);

    if (!fileExists) {
        file << "UserId,FirstName,LastName,Username,Email,Password\n";
    }
    int user_id = generateUserIdFromCSV(filename);

    file << user_id << ","
         << user.getFirstName() << ","
         << user.getLastName() << ","
         << user.getUsername() << ","
         << user.getEmail() << ","
         << user.getPassword() << "\n";
}

int CSVStorage::generateUserIdFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    int maxId{};

    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr;
        std::getline(ss, idStr, ',');
        try {
            int id = std::stoi(idStr);
            maxId =  std::max(maxId, id);
        } catch (...) {
            continue;
        }
    }

    return maxId + 1;
}