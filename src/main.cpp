#include "bank_account.h"
#include "main.h"

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
            cout << "2). Explore the features of the app\n";
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
                cout << "we are going for app tour." << endl;
                return;
            case 3:
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

    void logIn() {
        std::string first_name, last_name, username, email, password;

        cout << "Enter your first name: ";
        cin >> first_name;

        cout << "Enter your last name: ";
        cin >> last_name;
    }

int main() {

    welcome();

    /** 
 *  SavingAccount* acc = nullptr;
    SavingAccount* acc2 = nullptr;
    try {
            acc = new SavingAccount("Alice", "ACC123", 30000.0, 4.5);
        } catch (const std::invalid_argument& e) {
            cerr << "Failed to create Alice's account: " << e.what() << endl;
        }

    try {
            acc2 = new SavingAccount("Dennis", "ACC222", 30000.0, 4.5);
        } catch (const std::invalid_argument& e) {
            cerr << "Failed to create Dennis's account: " << e.what() << endl;
        }

    if (acc != nullptr) {
        //acc->showAccountDetails();
        cout << endl;
    }

    if (acc2 != nullptr) {
        acc2->showAccountDetails();
        acc2->transfer(*acc, 7000);
        acc2->withdraw(8000);
        cout << endl;
        acc2->showAccountDetails();
    }
    
    delete acc;
    delete acc2;
    */
    return 0;
}
