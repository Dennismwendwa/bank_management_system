#ifndef UTILS_HPP
#define UTILS_HPP
#include <string>
#include <chrono>
#include <random>
#include <sstream>
#include <iomanip>
#include <ctime>

std::string generateAccountNumber(int user_id);
std::string generateTransactionID();
std::string getCurrentDayTime();


#endif