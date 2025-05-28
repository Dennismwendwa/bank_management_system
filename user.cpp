#include "user.h"

User::User(std::string fn, std::string ln, std::string u, std::string em), first_name(fn) :
    last_name(ln), username(u), email(em) {
        password = "123456789"; // placeholder
    }

void User::setFirstName(std::string new_first_name) {
    first_name = new_first_name;
}

std::string User::getFirstName() {
    return first_name;
}

void User::setLastName(std::string new_last_name) {
    last_name = new_last_name;
}

std:: User::getLastName() {
    return last_name;
}
