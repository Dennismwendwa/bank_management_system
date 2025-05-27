#include "bank_account.h"

int main() {

    BankAccount acc("Alice", "ACC123", 1000.0);
    acc.setBalance(500.0);

    BankAccount acc2("Dennis", "ACC222", 10000.0);

    std::cout << "Account Holder: " << acc.getAccountHolder() << std::endl;
    std::cout << "Account Number: " << acc.getAccountNumber() << std::endl;
    cout << "Balance: " << acc.getBalance() << endl;
    cout << endl;
    cout << endl;

    std::cout << "Account Holder: " << acc2.getAccountHolder() << std::endl;
    std::cout << "Account Number: " << acc2.getAccountNumber() << std::endl;
    cout << "Balance: " << acc2.getBalance() << endl;
    cout << endl;
    cout << endl;

    acc.deposit(333.0);
    cout << "Balance: " << acc.getBalance() << endl;

    acc2.withdraw(4444.0);
    cout << "Balance: " << acc2.getBalance() << endl;
    
    acc2.transfer(acc, 666.0);
    cout << "Balance: " << acc2.getBalance() << endl;
    cout << "Balance: " << acc.getBalance() << endl;

    return 0;
}
