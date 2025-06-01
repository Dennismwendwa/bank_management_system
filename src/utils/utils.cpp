#include "utils.hpp"

std::string generateAccountNumber(int user_id) {
    auto now = std::chrono::system_clock::now();
    auto micros = std::chrono::duration_cast<std::chrono::microseconds>(
        now.time_since_epoch()).count();

    std::mt19937 rng(micros);
    std::uniform_int_distribution<> dist(100000, 999999);

    std::stringstream ss;
    ss << "SAV"
       << std::setw(3) << std::setfill('0') << (user_id % 1000)
       << dist(rng);

    return ss.str();
}