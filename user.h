#ifndef USER_H
#define USER_H
#include <iostream>
#include <iostream>


using namespace std;

class User {
    public:
        void setFirstName(std::string new_first_name);
        std::string getFirstName();
        void setLastName(std::string new_last_name);
        std::string getLastName();
        void setUsername(std::string new_username);
        std::getUsername();
        void setEmail(std::string new_email);
        std::string getEmail();
        void setPassword(std::string new_password);
        std::getPassword();

    private:
        std::string first_name;
        std::string last_name;
        std::string username;
        std::string email;
        std::string password;

};

#endif
