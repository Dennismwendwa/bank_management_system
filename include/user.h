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
        std::string getFirstName() const;
        std::string getLastName() const;
        std::string getUsername() const;
        std::string getEmail() const;
        std::string getPassword() const;
        bool getLoginStatus() const;
        int getUserId() const;

        void setFirstName(std::string new_first_name);
        void setLastName(std::string new_last_name);
        void setUsername(std::string new_username);
        void setEmail(std::string new_email);
        void setPassword(std::string new_password);
        void setLoginStatus(bool new_status);

        static User fromCSV(const std::string& csvLine);
    
    protected:
        int user_id;

    private:
        User(std::string fn, std::string ln, std::string u, std::string em, std::string pw);
        User(int u_id, std::string fn, std::string ln, std::string u, std::string em, std::string pw);
        std::string first_name;
        std::string last_name;
        std::string username;
        std::string email;
        std::string password;
        bool login_status{false};

        static bool isUsernameTaken(const std::string& username);
        static bool isEmailTaken(const std::string& email);
        static void saveUserToFile(const User& user);
};

#endif
