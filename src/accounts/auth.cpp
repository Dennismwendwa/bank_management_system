#include "auth.hpp"
//#include "bcrypt/BCrypt.hpp"

Auth::Auth(std::shared_ptr<IStorage> storage) : storage(std::move(storage)) {}

bool Auth::registerUser(
    const std::string& firstName,
    const std::string& lastName,
    const std::string& username,
    const std::string& email,
    const std::string& password) {
        if (password.length() < 9) {
            std::cerr << "Password too short." << std::endl;
            throw std::runtime_error("Password must be at least 9 characters long.");
            return false;
        }

        if (storage->isUsernameTaken(username)) {
            throw std::runtime_error("Username '" + username + "' is already taken.");
            return false;
        }

        if (storage->isEmailTaken(email)) {
            throw std::runtime_error("Email '" + email + "' is already in use.");
            return false;
        }

        std::string hashedPassword = password; // BCrypt::generateHash(password);
        User user = User::createUser(firstName, lastName, username, email, hashedPassword);

        return storage->saveUser(user);
    }

std::optional<User> Auth::login(const std::string& username, const std::string& password) {
    auto userOpt = storage->findUserByUsername(username);
    if (!userOpt.has_value()) {
        std::cerr << "User not found." << std::endl;
        return std::nullopt;
    }

    User& user = userOpt.value();
    if (password == user.getPassword()) {
        user.setLoginStatus(true);
        return user;
    } else {
        return std::nullopt;
    }
    //return BCrypt::validatePassword(password, user.getPassword());
}