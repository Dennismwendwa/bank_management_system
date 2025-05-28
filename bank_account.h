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


class SavingAccount : public BankAccount {
    public:
        SavingAccount(std::string ah, std::an, double b, std::date, double rate
                ) : BackAccount(ah, an, b), created_on(date), interest_rate(rate);

    private:
        std::string created_on;
        double interest_rate;
        double minimum_balance;
        int monthly_withdraws;
        int max_withdrawals;
        std::string account_type;
};
#endif
