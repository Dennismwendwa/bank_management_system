#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <memory>
#include <cctype>
#include "auth.hpp"

inline std::shared_ptr<User> current_user = nullptr;

using namespace std;

void selectOptions();
void registerUser(Auth& auth);

#endif