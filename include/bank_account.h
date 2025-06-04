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
        BankAccount(int user_id, std::string ah, std::string an, std::string ID);
        BankAccount(int user_id, std::string ah, std::string an, double b, std::string ID);
        BankAccount(int acc_id, int user_id, std::string ah, std::string an, double b, std::string ID);

        void setAccountNumber(std::string new_number);
        std::string getAccountNumber() const;
        void setAccountHolder(std::string new_holder);
        std::string getAccountHolder() const;
        void setBalance (double new_balance);
        void setNationalId(std::string new_id);
        void setAccountId(int new_id);

        void deposit(double deposit);
        void withdraw(double amount);
        void transfer(BankAccount& to, double amount);
        int getUserId() const;
        int getAccountId() const;
        double getBalance() const;
        std::string getNationalId() const;

    protected:
        int account_id;
        int user_id;

    private:
        std::string account_holder;
        std::string account_number;
        double balance;
        std::string nationl_id;

};


class SavingAccount : public BankAccount {
    public:
        SavingAccount(int user_id, std::string ah, std::string an, double b, std::string ni, double rate);
        SavingAccount(int account_id, int user_id, std::string account_holder, std::string account_number,
                    double balance, std::string ni, double interest_rate, double minimum_balance,
                    int monthly_withdrawals, int max_withdrawals,
                    std::string account_type, std::string created_on);

	void setCreatedOn(std::string new_date);
    std::string getCurrentDate() const;
	std::string getCreatedOn() const;
	void setInterestRate(double new_intrest_rate);
    double getInterestRate() const;
	void setMinimumBalance(double new_balance);
	double getMinimumBalance() const;
	void setMonthlyWithdrawals(int new_withdrawals);
	int getMonthlyWithdrawals() const;
	void setMaxWithdrawals(int new_max);
	int getMaxWithdrawals() const;
	void setAccountType(std::string new_type);
	std::string getAccountType() const;
    void showAccountDetails();
    void withdraw(double amount);
    void transfer(SavingAccount& to, double amount);
    static SavingAccount CreateAccount(int user_id,
                              std::string account_holder,
                              double amount, std::string national_id, double rate);

    private:
        std::string created_on;
        double interest_rate;
        double minimum_balance;
        int monthly_withdrawals;
        int max_withdrawals;
        std::string account_type;

        void addMonthlyWithdrawals(int new_number);
};


class Transaction {

    public:
        Transaction(std::string transaction_id, std::string date_time,
                    std::string transaction_type, std::string account_holder,
                    std::string source_account, double amount,
                    std::string currency, std::string description,
                    std::string status, std::string method);
        Transaction(int id,
                    std::string transaction_id, std::string date_time,
                    std::string transaction_type, std::string account_holder,
                    std::string source_account, double amount,
                    std::string currency, std::string description,
                    std::string status, std::string method);

        void setTransactionId(std::string new_transaction_id);
        void setDatetime(std::string new_date_time);
        void setTransactionType(std::string new_transaction_type);
        void setAccountHolder(std::string new_account_holder);
        void setSourceAccount(std::string new_source_account);
        void setDestinationAccount(std::string new_destination_account);
        void setamount(double amount);
        void setCurrency(std::string new_currency);
        void setDescription(std::string new_descriction);
        void setStatus(std::string new_status);
        void std::string method(std::new_method);

        std::string getTransactionId();
        std::string getDatetime();
        std::string getTransactionId();
        std::string getAccountHolder();
        std::optional<std::string> getSourceAccount();
        std::optional<std::string> getDestinationAccount();
        double getAmount();
        std::string getCurrency();
        std::string getDescription();
        std::string getStatus();
        std::string getMethod();

    private:
        int id; // primary key
        std::string transaction_id;
        std::string date_time;
        std::string transaction_type;

        std::string account_holder;
        std::optional<std::string> sourceAccount; //
        std::optional<std::string> destinationAccount; //

        double amount;
        std::string currency;
        std::string description;

        std::string status;
        std::string method;
};


class Ledger {

    private:
        std::vector<Transaction> transactions;

    public:
        Ledger(Transaction& t);
        void addTransaction(const Transaction& t);
        const std::vector<Transaction>& getAllTransactions() const;
        std::vector<Transaction> getTransactionsByAccountHolder(const std::string& accountHolder) const;
        std::vector<Transaction> getTransactionsByType(const std::string& type) const;
        double computeNetBalance() const;
        double computeAccountBalance(const std::string& account) const;
        double computeTotalByType(const std::string& type) const;
        void printAll() const;
};
#endif
