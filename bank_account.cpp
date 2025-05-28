#include "bank_account.h"

BankAccount::BankAccount(std::string ah, std::string an) {
    account_holder = ah;
    account_number = an;
    balance = 0;
}

BankAccount::BankAccount(std::string ah, std::string an, double b) {
    account_holder = ah;
    account_number = an;
    balance = b;
}

void BankAccount::setAccountNumber(std::string new_number) {
    account_number = new_number;
}

std::string BankAccount::getAccountNumber() {
    return account_number;
}

void BankAccount::setAccountHolder(std::string new_holder) {
    account_holder = new_holder;
}

std::string BankAccount::getAccountHolder() {
    return account_holder;
}

void BankAccount::setBalance (double new_balance) {
    if (balance > 0) {
        balance += new_balance;
    }
}

double BankAccount::getBalance() {
    return balance;
}

void BankAccount::deposit(double deposit) {
    balance += deposit;
    cout << "You have deposited " << deposit << endl;
    cout << "New Balance: " << getBalance() << endl;
}

void BankAccount::withdraw(double amount) {
    if ((balance - 100) > amount) {
        if ( balance > 50) {
            balance -= amount;
            cout << "You have withdrawn ksh" << amount << endl;
            cout << "New balance is ksh" << getBalance() << endl;
        } else {
            cout << "Minimum withdraw amount is ksh50: " << endl;
        }
    } else {
        cout << "Incefincent funds!" << endl;
        cout << "Balance: " << getBalance() << endl;
        cout << "Avaialable Balance: " << getBalance() - 100 << endl;
    }
}

void BankAccount::transfer(BankAccount& to, double amount) {
    if (getBalance() - 100 > amount) {
        if (amount > 0) {
            balance -= amount;
            to.deposit(amount);
            cout << "Transferred Ksh " << amount << " to account ";
            cout << to.getAccountNumber() << std::endl;
        }
    } else {
        cout << "Incefincent funds!" << endl;
        cout << "Balance: " << getBalance() << endl;
        cout << "Avaialable Balance: " << getBalance() - 100 << endl;
    }
}

SavingAccount::SavingAccount(std::string ah, std::an, double b, std::date, double rate
        ) : BackAccount(ah, an, b), created_on(date), interest_rate(rate) {
        minimum_balance = 10000;
        monthly_withdrawals = 0;
        max_withdrawals = 3;
        account_type = "Basic";
    }

void SavingAccount::setCreatedOn(std::string new_date) {
    created_on = new_date;
}
std::string getCreatedOn() {
    return created_on;
}

void SavingAccount::setInterestRate(double new_interest_rate) {
    interest                                                                 
}
