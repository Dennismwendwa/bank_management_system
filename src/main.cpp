#include "bank_account.h"
#include "main.h"
#include "auth.hpp"
#include "storage_factory.hpp"

    void welcome() {
        cout << "\n============================================================\n";
        cout << "           🌟 Welcome to Dennis' Banking App 🌟\n";
        cout << "============================================================\n\n";
        cout << "How can we assist you today?\n";
        cout << "Please choose an option below:\n";
        getChoice();
    }

    void getChoice() {
        int choice{};

        while(true) {
            cout << "Choices.\n";
            cout << "1). Login\n";
            cout << "2). Register new user.\n";
            cout << "3). Explore the features of the app\n";
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
                return;
            case 2:
                cout << "Register new user." << endl;
                registerUser();
                return;
            case 3:
                cout << "we are going for app tour." << endl;
                return;
            case 4:
                cout << "Exiting the app. Goodbye!\n";
                return;
            default:
                cout << "Invalid option. Please try again:" << endl;
                break;
            }
        }
    }

    void selectOptions() {
        cout << "more options here";
    }

    void registerUser() {
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
            auto storage = createStorage();
            cout << "\nStorage:: " << storage << endl;
            Auth auth(storage);
            auth.registerUser(first_name, last_name, username, email, password);
            std::cout << "Users created successfully.\n";
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

int main() {

    welcome();

    return 0;
}
