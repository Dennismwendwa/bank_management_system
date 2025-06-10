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
#include <optional>
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
    friend class Bank;
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


    private:
        std::string created_on;
        double interest_rate;
        double minimum_balance;
        int monthly_withdrawals;
        int max_withdrawals;
        std::string account_type;

        void addMonthlyWithdrawals(int new_number);

        void showAccountDetails();
        void withdraw(double amount);
        void transfer(SavingAccount& to, double amount);
        static SavingAccount CreateAccount(int user_id,
                                std::string account_holder,
                                double amount, std::string national_id, double rate);
        void deposit(double amount);
};


class Transaction {
    public:
        Transaction(std::string transaction_id, std::string date_time,
                    std::string transaction_type, std::string account_holder,
                    double amount,
                    std::string currency, std::string description,
                    std::string status, std::string method,
                    std::string source_account,
                    std::optional<std::string> destination_account = std::nullopt);
        Transaction(int id,
                    std::string transaction_id, std::string date_time,
                    std::string transaction_type, std::string account_holder,
                    double amount,
                    std::string currency, std::string description,
                    std::string status, std::string method,
                    std::string source_account,
                    std::optional<std::string> destination_account = std::nullopt);

        void setTransactionId(std::string new_transaction_id);
        void setDatetime(std::string new_date_time);
        void setTransactionType(std::string new_transaction_type);
        void setAccountHolder(std::string new_account_holder);
        void setSourceAccount(std::string new_source_account);
        void setDestinationAccount(std::string new_destination_account);
        void setamount(double new_amount);
        void setCurrency(std::string new_currency);
        void setDescription(std::string new_descriction);
        void setStatus(std::string new_status);
        void setMethod(std::string new_method);
        void setPrimaryKey(int new_id);
        
        int getPrimaryKey() const;
        std::string getTransactionId() const;
        std::string getDatetime() const;
        std::string getAccountHolder() const;
        std::optional<std::string> getSourceAccount() const;
        std::optional<std::string> getDestinationAccount() const;
        double getAmount() const;
        std::string getCurrency() const;
        std::string getDescription() const;
        std::string getStatus() const;
        std::string getMethod() const;
        std::string getTransactionType() const;

        static Transaction createTransaction(
            const std::string& transaction_id, const std::string& date_time,
            const std::string& transaction_type, const std::string& account_holder,
            double amount, const std::string& currency, const std::string& description,
            const std::string& status, const std::string& method,
            const std::string source_account,
            std::optional<std::string> destination_account = std::nullopt
        );

    private:
        int id; // primary key
        std::string transaction_id;
        std::string date_time;
        std::string transaction_type;

        std::string account_holder;
        double amount;
        std::string currency;

        std::string description;
        std::string status;
        std::string method;

        std::string source_account;
        std::optional<std::string> destination_account = std::nullopt; //
};

class Ledger {
    private:
        Ledger(const Transaction& t, std::string accountNumber, std::string currency, std::string date);
        Ledger(int id, const Transaction& t, std::string accountNumber, std::string currency, std::string date);

        int id;
        Transaction transaction;
        std::string account_number;
        std::string date;
        std::string currency;

    public:
        std::string getAccountNumber() const;
        std::string getDate() const;
        std::string getCurrency() const;
        int getPrimaryKey() const;
        void setPrimaryKey(int new_pk);
        const Transaction& getTransaction() const;

        double computeNetBalance() const;
        double computeAccountBalance(const std::string& account) const;
        double computeTotalByType(const std::string& type) const;
        void printAll() const;

        static Ledger createLedger(
            const Transaction& transaction, const std::string& account_holder,
            const std::string& currency, const std::string& date);

        static Ledger createLedger(int is,
            const Transaction& transaction, const std::string& account_holder,
            const std::string& currency, const std::string& date);
};


class AccountStatement {
    friend class Bank;
    private:
        std::string account_number;
        std::string start_date;
        std::string end_date;

        std::vector<Ledger> ledgers_in_range;

        double opening_balance = 0;
        double closing_balance = 0;
        double total_debits = 0;
        double total_credits = 0;

    public:
        AccountStatement(
            const std::string& account,
            const std::string& start_date,
            const std::string& end_date,
            const std::vector<Ledger>& all_ledgers);

        void printStatement() const;
};


#endif
