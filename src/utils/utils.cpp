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

std::string generateTransactionID() {
    auto now = std::chrono::system_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()).count();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1000, 9999);

    std::stringstream ss;
    ss << "TXN" << ms << dis(gen);
    return ss.str();
}

std::string getCurrentDayTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M-%S");
    return oss.str();
}