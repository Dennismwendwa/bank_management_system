#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <locale>
#include <stdexcept>
#include <vector>
using namespace std;

class BankAccount {
    public:
        BankAccount(int user_id, std::string ah, std::string an);
        BankAccount(int user_id, std::string ah, std::string an, double b);
        BankAccount(int acc_id, int user_id, std::string ah, std::string an, double b);

        void setAccountNumber(std::string new_number);
        std::string getAccountNumber();
        void setAccountHolder(std::string new_holder);
        std::string getAccountHolder();
        void setBalance (double new_balance);
        double getBalance();

        void deposit(double deposit);
        void withdraw(double amount);
        void transfer(BankAccount& to, double amount);
        int getUserId() const;
        int getAccountId() const;

    protected:
        int account_id;
        int user_id;

    private:
        std::string account_holder;
        std::string account_number;
        double balance;

};


class SavingAccount : public BankAccount {
    public:
        SavingAccount(int user_id, std::string ah, std::string an, double b, double rate);
    //SavingAccount newAcc(10, "Dennis Mwendwa", "1234567890", 17000.0, 4.5)

	void setCreatedOn(std::string new_date);
    std::string getCurrentDate();
	std::string getCreatedOn();
	void setInterestRate(double new_intrest_rate);
    double getInterestRate();
	void setMinimumBalance(double new_balance);
	double getMinimumBalance();
	void setMonthlyWithdrawals(int new_withdrawals);
	int getMonthlyWithdrawals();
	void setMaxWithdrawals(int new_max);
	int getMaxWithdrawals();
	void setAccountType(std::string new_type);
	std::string getAccountType();
    void showAccountDetails();
    void withdraw(double amount);
    void transfer(SavingAccount& to, double amount);
    std::string CreateAccount(int user_id,
                              std::string account_holder,
                              double amount, double rate);

    private:
        std::string created_on;
        double interest_rate;
        double minimum_balance;
        int monthly_withdrawals;
        int max_withdrawals;
        std::string account_type;

        void addMonthlyWithdrawals(int new_number);
};
#endif
