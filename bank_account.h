#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BankAccount {
    public:
        BankAccount(std::string ah, std::string an);
        BankAccount(std::string ah, std::string an, double b);

        void setAccountNumber(std::string new_number);
        std::string getAccountNumber();

        void setAccountHolder(std::string new_holder);
        std::string getAccountHolder();

        void setBalance (double new_balance);
        double getBalance();

        void deposit(double deposit);
        void withdraw(double amount);
        void transfer(BankAccount& to, double amount);

    private:
        std::string account_holder;
        std::string account_number;
        double balance;

};
#endif
