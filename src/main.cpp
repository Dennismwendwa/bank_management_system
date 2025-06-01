#include "bank_account.h"
#include "main.h"
#include "storage_factory.hpp"

    void selectOptions() {
        cout << "more options here";
    }

    void registerUser(Auth& auth) {
        std::string first_name, last_name, username, email, password;

        cout << "Enter your first name: ";
        cin >> first_name;

        cout << "Enter your last name: ";
        cin >> last_name;

        cout << "Enter your username: ";
        cin >> username;

        cout << "Enter your email: ";
        cin >> email;

        cout << "Enter your password: ";
        cin >> password;

        try {
            auth.registerUser(first_name, last_name, username, email, password);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

    void login(Auth& auth) {
        std::string username, password;
        cout << "Enter your username: ";
        cin >> username;

        cout << "Enter your password: ";
        cin >> password;

        std::optional<User> user = auth.login(username, password);
        if (user) {
            std::cout << "\nHello, " << user->getFirstName() << "!\n\n";
        } else {
            std::cout << "Login failed.\n";
        }

    }

int main() {

    auto storage = createStorage();
    Auth auth(storage);

    int choice{};
    bool flag{true};
    bool bank_options{true};

    cout << "\n============================================================\n";
    cout << "           🌟 Welcome to Dennis' Banking App 🌟\n";
    cout << "============================================================\n\n";
    cout << "How can we assist you today?\n";
    cout << "Please choose an option below:\n";

    do {
        cout << "Choices.\n";
        cout << "1). Login\n";
        cout << "2). Register new user.\n";
        cout << "3). Explore the features of the app.\n";
        cout << "4). Exit.\n";
        cout << "Your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number:" << endl;
            continue;
        }

        switch (choice)
        {
        case 1:
            cout << "loging in now." << endl;
            login(auth);
            flag = false;
            break;
        case 2:
            cout << "Register new user." << endl;
            registerUser(auth);
            break;
        case 3:
            cout << "we are going for app tour." << endl;
            break;
        case 4:
            cout << "Exiting the app. Goodbye!\n";
            flag = false;
            break;
        default:
            cout << "Invalid option. Please try again:" << endl;
            break;
        }
    } while(flag);

    cout << "Bank services" << endl;
    cout << "\n============================================================\n";
    cout << "           🌟 Our Banking Services 🌟\n";
    cout << "============================================================\n\n";
    cout << "How can we assist you today?\n";
    cout << "Choose one option." << endl;

    do {
        int my_choice{0};

        cout << "1). Open account.\n";
        cout << "2). Deposit money.\n";
        cout << "3). Withdraw money.\n";
        cout << "4). Transfer money.\n";
        cout << "5). Exit.\n";
        cout << "Your choise: ";

        cin >> my_choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number:" << endl;
            continue;
        }

        switch (my_choice)
        {
        case 1:
            /* code */
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            cout << "Exiting now. Bye Bye.";
            bank_options = false;
            break;
        
        default:
            cout << "Invalid option. Please try again:" << endl;
            break;
        }

    } while (bank_options);

    return 0;
}
