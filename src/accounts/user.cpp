#include "user.h"
//#include "bcrypt/BCrypt.hpp"

namespace fs = std::filesystem;
const std::string USER_FILE = "users.csv";

User::User(std::string fn, std::string ln, std::string u, std::string em, std::string pw) : first_name(fn),
    last_name(ln), username(u), email(em), password(pw) {}

std::string User::getFirstName() const { return first_name; }
std::string User::getLastName() const { return last_name; }
std::string User::getUsername() const { return username; }
std::string User::getEmail() const { return email; }
std::string User::getPassword() const { return password; }

void User::setFirstName(std::string new_first_name) { first_name = new_first_name; }
void User::setLastName(std::string new_last_name) { last_name = new_last_name; }
void User::setUsername(std::string new_username) { username = new_username; }
void User::setEmail(std::string new_email) { email = new_email; }
void User::setPassword(std::string new_password) {
    //password = BCrypt::generateHash(new_password); 
    password = new_password;
}

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