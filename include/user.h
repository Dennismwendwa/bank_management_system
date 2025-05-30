#ifndef USER_H
#define USER_H
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <filesystem>
#include <sstream>

using namespace std;

class User {
    public:
        static User createUser(std::string fn, std::string ln, std::string u,
                           std::string em, std::string pw);
        void setFirstName(std::string new_first_name);
        std::string getFirstName();
        void setLastName(std::string new_last_name);
        std::string getLastName();
        void setUsername(std::string new_username);
        std::string getUsername();
        void setEmail(std::string new_email);
        std::string getEmail();
        void setPassword(std::string new_password);
        std::string getPassword() const;

    private:
        User(std::string fn, std::string ln, std::string u, std::string em, std::string pw);
        std::string first_name;
        std::string last_name;
        std::string username;
        std::string email;
        std::string password;

        static bool isUsernameTaken(const std::string& username);
        static bool isEmailTaken(const std::string& email);
        static void saveUserToFile(const User& user);
};

#endif
