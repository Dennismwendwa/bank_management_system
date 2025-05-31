#ifndef CSV_STORAGE_HPP
#define CSV_STORAGE_HPP

#include <fstream>
#include <sstream>
#include <vector>
#include <optional>
#include <mutex>
#include "storage.hpp"

class CSVStorage : public IStorage {
    public:
        explicit CSVStorage(const std::string& filename);

        bool saveUser(const User& user) override;
        bool isUsernameTaken(const std::string& username) override;
        bool isEmailTaken(const std::string& email) override;
        std::optional<User> findUserByUsername(const std::string& username) override;

    private:
        std::string filename;
        std::mutex fileMutex;

        std::vector<User> loadAllUsers();
        void appendUserToFile(const User& user);
};

#endif