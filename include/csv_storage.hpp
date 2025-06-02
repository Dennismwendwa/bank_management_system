#ifndef CSV_STORAGE_HPP
#define CSV_STORAGE_HPP

#include <fstream>
#include <sstream>
#include <vector>
#include <optional>
#include <mutex>
#include <algorithm>
#include <string>
#include "storage.hpp"

class CSVStorage {
    public:
        explicit CSVStorage(const std::string& filename);

        bool saveUser(const User& user);
        bool isUsernameTaken(const std::string& username);
        bool isEmailTaken(const std::string& email);
        std::optional<User> findUserByUsername(const std::string& username);

    private:
        std::string filename;
        std::mutex fileMutex;

        std::vector<User> loadAllUsers();
        std::vector<User> loadUsersFromFileUnlocked();
        void appendUserToFile(const User& user);
        int generateUserIdFromCSV(const std::string& filename);
};
#endif