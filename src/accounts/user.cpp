#include "user.h"
//#include "bcrypt/BCrypt.hpp"

namespace fs = std::filesystem;
const std::string USER_FILE = "users.csv";

User::User(std::string fn, std::string ln, std::string u, std::string em, std::string pw) : first_name(fn),
    last_name(ln), username(u), email(em), password(pw) {}

void User::setFirstName(std::string new_first_name) { first_name = new_first_name; }
std::string User::getFirstName() { return first_name; }
void User::setLastName(std::string new_last_name) { last_name = new_last_name; }
std::string User::getLastName() { return last_name; }
void User::setUsername(std::string new_username) { username = new_username; }
std::string User::getUsername() { return username; }
void User::setEmail(std::string new_email) { email = new_email; }
std::string User::getEmail() { return email; }
void User::setPassword(std::string new_password) {
    //password = BCrypt::generateHash(new_password); 
    password = new_password;
}
std::string User::getPassword() const {return password; }

User User::createUser(std::string fn, std::string ln,
                             std::string u, std::string em, std::string pw) {
    User user(fn, ln, u, em, pw);
    saveUserToFile(user); // to move this to storage
    return user;
}

bool User::isUsernameTaken(const std::string& username) {
    std::ifstream file(USER_FILE);
    std::string line;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string fn, ln, u, em, pw;

        getline(ss, fn, ',');
        getline(ss, ln, ',');
        getline(ss, u, ',');
        if (u == username) return true;
    }
    return false;
}

bool User::isEmailTaken(const std::string& email) {
    std::ifstream file(USER_FILE);
    std::string line;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string fn, ln, u, em, pw;

        getline(ss, fn, ',');
        getline(ss, ln, ',');
        getline(ss, u, ',');
        getline(ss, em, ',');
        if (em == email) return true;
    }
    return false;
}

void User::saveUserToFile(const User& user) {
    bool file_exists = std::filesystem::exists(USER_FILE);
    std::ofstream file(USER_FILE, std::ios::app);

    if (!file_exists) {
        file << "first_name,last_name,username,email,password\n";
    }

    file << user.first_name << ","
        << user.last_name << ","
        << user.username << ","
        << user.email << ","
        << user.password << "\n";
        //<< BCrypt::generateHash(user.password) << "\n";
}

/**
 * if (BCrypt::validatePassword(password, hash)) {
    std::cout << "Password is valid!" << std::endl;
} else {
    std::cout << "Invalid password!" << std::endl;
}
 * 
 */