#include "auth.hpp"
#include "bcrypt/BCrypt.hpp"

Auth::Auth(std::shared_ptr<IStorage> storage) : storage(std::move(storage)) {}

bool Auth::registerUser(
    const std::string& firstName,
    const std::string& lastName,
    const std::string& username,
    const std::string& email,
    const std::string& password) {
        if (password.length() < 9) {
            std::cerr << "Password too short." << std::endl;
            return false;
        }

        if (storage->isUsernameTaken(username)) {
            std::cerr << "Username already in use." << std::endl;
            return false;
        }

        if (storage->isEmailTaken(email)) {
            std::cerr << "Email taken." << std::endl;
            return false;
        }

        std::string hashedPassword = BCrypt::generateHash(password);
        User user = User::createUser(firstName, lastName, username, email, hashedPassword);

        return storage->saveUser(user);
    }

bool Auth::login(const std::string& username, const std::string& password) {
    auto userOpt = storage->findUserByUsername(username);
    if (!userOpt.has_value()) {
        std::cerr << "User not found." << std::endl;
        return false;
    }

    const User& user = userOpt.value();
    return BCrypt::validatePassword(password, user.getPassword());
}