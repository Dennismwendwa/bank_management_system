#include "bank_account.h"

int main() {

    SavingAccount* acc = nullptr;
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
    return 0;
}
