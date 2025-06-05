#include "bank_account.h"
#include "main.h"
#include "storage_factory.hpp"
#include "bank_ops.hpp"


    void selectOptions() {
        
    }

    std::string trim(const std::string& str) {
        auto start = std::find_if_not(str.begin(), str.end(), ::isspace);
        auto end = std::find_if_not(str.rbegin(), str.rend(), ::isspace).base();
        return (start < end) ? std::string(start, end) : "";
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

    bool login(Auth& auth) {
        std::string username, password;
        cout << "Enter your username: ";
        cin >> username;

        cout << "Enter your password: ";
        cin >> password;

        std::optional<User> user = auth.login(username, password);
        if (user) {
            current_user = std::make_shared<User>(*user);
            return true;
        } else {
            std::cout << "Login failed.\n";
            return false;
        }

    }

int main() {

    auto storage = createStorage();
    Auth auth(storage);
    Bank bank(storage);

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
            if (login(auth)) {
                flag = false;
            } else {
                cout << "\n Login failed\n\n";
            }
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
        case 1: {
            std::string names, id_number;
            double amount;
            cout << "Enter your names: ";
            cin >> names;
            cout << "Enter your ID number/ Passport number: ";
            cin >> id_number;
            cout << "Enter the amount to deposit: ";
            cin >> amount;

            //SavingAccount newAcc(current_user->getUserId(), names, "1234567890", amount, 4.5);
            double rate = 4.5;
            //SavingAccount acc_c = SavingAccount::CreateAccount(current_user->getUserId(), names, amount, id_number, rate);
            try {
                bank.openAccount(current_user->getUserId(), names, amount, id_number, rate);
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << "\n";
            }
            break;
        }
        case 2:{
            std::string account_number, id_number;
            double amount;
            cout << "Enter your account number: ";
            cin >> account_number;
            std::cin.ignore();

            cout << "Enter your ID number/ Passport number: ";
            cin >> id_number;
            std::cin.ignore();

            cout << "Enter the amount to deposit: ";
            cin >> amount;
            std::cin.ignore();
            
            try {
                bank.deposit(account_number, id_number, amount);
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << "\n";
            }
            break;
        }
        case 3: {
            cout << "About to withdrawal money now.\n";
            std::string account_number;
            double amount{0};
            cout << "Enter account number: ";
            cin >> account_number;

            cout << "Enter amount: ";
            cin>> amount;
            try {
                bank.withdraw(account_number, amount);
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << "\n";
            }
            break;
        }
        case 4: {
            std::string from_account, to_account, id_number, names;
            double amount;
            cout << "\nAbout to transfer money" << endl;
            cout << "Enter your name: ";
            cin >> names;
            cout << "Enter your ID number: ";
            cin >> id_number;
            cout << "Enter your account number: ";
            cin >> from_account;
            cout << "Enter Account to transfer money to: ";
            cin >> to_account;
            cout << "Enter amount to transfer: ";
            cin >> amount;
            try {
                bank.transfer(id_number, from_account, to_account, amount);
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << "\n";
            }
            break;
        }
        case 5: {
            cout << "Exiting now. Bye Bye.";
            bank_options = false;
            break;
        }
        default:
            cout << "Invalid option. Please try again:" << endl;
            break;
        }

    } while (bank_options);

    return 0;
}
