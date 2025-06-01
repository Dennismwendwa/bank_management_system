#include "bank_account.h"
#include "user.h"
#include "utils.hpp"

BankAccount::BankAccount(int user_id, std::string ah, std::string an) {
    user_id = user_id, account_holder = ah, account_number = an, balance = 0;
}

BankAccount::BankAccount(int ud, std::string ah, std::string an, double b) {
    const double MIN_BALANCE = 10000.0;

    if (b < MIN_BALANCE) {
        throw std::invalid_argument("Initial balance must be at least Ksh 10,000.");
    }
    user_id = ud,
    account_holder = ah;
    account_number = an;
    balance = b;
}
BankAccount::BankAccount(int acc_id, int user_id, std::string ah, std::string an, double b)
    : account_id(acc_id), user_id(user_id), account_holder(ah), account_number(an), balance(b) {}

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
    balance = new_balance;
}

double BankAccount::getBalance() {
    return balance;
}

int BankAccount::getAccountId() const {return account_id; }
int BankAccount::getUserId() const {return user_id; }

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

SavingAccount::SavingAccount(int user_id, std::string ah, std::string an, double b, double rate
        ) : BankAccount(user_id, ah, an, b), created_on(getCurrentDate()), interest_rate(rate) {
        minimum_balance = 10000;
        monthly_withdrawals = 0;
        max_withdrawals = 3;
        account_type = "Basic";
    }
std::string SavingAccount::getCurrentDate() {
    std::time_t now = std::time(nullptr);
    std::tm* local_time = std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(local_time, "%Y-%m-%d");
    return oss.str();
}

void SavingAccount::setCreatedOn(std::string new_date) {
    created_on = new_date;
}
std::string SavingAccount::getCreatedOn() {
    return created_on;
}

void SavingAccount::setInterestRate(double new_interest_rate) {
    interest_rate = new_interest_rate;                                                  
}

double SavingAccount::getInterestRate() {
    return interest_rate;
}

void SavingAccount::setMinimumBalance(double new_balance) {
    minimum_balance = new_balance;
}

double SavingAccount::getMinimumBalance() {
    return minimum_balance;
}

void SavingAccount::setMonthlyWithdrawals(int new_withdrawals) {
    monthly_withdrawals = new_withdrawals;
}
void SavingAccount::addMonthlyWithdrawals(int new_number) {
    cout << "Increasing withdraws\n";
    if (new_number == 1) {
        monthly_withdrawals += new_number;
    }
}

int SavingAccount::getMonthlyWithdrawals() {
    return monthly_withdrawals;
}

void SavingAccount::setMaxWithdrawals(int new_max) {
    max_withdrawals = new_max;
}

int SavingAccount::getMaxWithdrawals() {
    return max_withdrawals;
}

void SavingAccount::setAccountType(std::string new_type) {
    account_type = new_type;
}

std::string SavingAccount::getAccountType() {
    return account_type;
}

void SavingAccount::showAccountDetails() {
    cout.imbue(locale(""));

    cout << "\n================== Account Summary ==================\n";
    cout << left << setw(25) << "Date:" << getCurrentDate() << endl;
    cout << left << setw(25) << "Account Type:" << "Saving account (" + getAccountType() + ")" << endl;
    cout << left << setw(25) << "Opening Date:" << getCreatedOn() << endl;

    cout << "\n------------------ Holder Details -------------------\n";
    cout << left << setw(25) << "Account Holder:" << getAccountHolder() << endl;
    cout << left << setw(25) << "Account Number:" << getAccountNumber() << endl;
    cout << left << setw(25) << "User table-id: " << getUserId() << endl;

    cout << "\n------------------ Financial Info -------------------\n";
    cout << left << setw(25) << "Account Balance: Ksh" << fixed << setprecision(2) << getBalance() << endl;
    cout << left << setw(25) << "Interest Rate:" << getInterestRate() << " %" << endl;
    cout << left << setw(25) << "Minimum Balance: Ksh" << getMinimumBalance() << endl;
    cout << left << setw(25) << "Withdrawals/Month:" << getMonthlyWithdrawals() << endl;
    cout << left << setw(25) << "Max Withdrawals/Month:" << getMaxWithdrawals() << endl;

    cout << "======================================================\n" << endl;;
}

void SavingAccount::withdraw(double amount) {
    if (getMonthlyWithdrawals() >= getMaxWithdrawals()) {
        cout << "You have reached the allowed withdrawls per month." << endl;
    } else {
        if (getBalance() >= amount) {
            setBalance(getBalance() - amount);
            monthly_withdrawals++;
        } else {
            cout << "Incefficent funds." << endl;
            cout << "Balance amount: " << getBalance() << endl;
        }
    }
}

void SavingAccount::transfer(SavingAccount& to, double amount) {
    if (getBalance() - getMinimumBalance() > amount) {
        if (amount > 0) {
            setBalance(getBalance() - amount);
            to.setBalance(to.getBalance() + amount);
            monthly_withdrawals++;
            cout << "Transferred Ksh " << amount << " to account ";
            cout << to.getAccountNumber() << std::endl;
        }
    } else {
        cout << "Incefincent funds!" << endl;
        cout << "Balance: " << getBalance() << endl;
        cout << "Avaialable Balance: " << getBalance() - 100 << endl;
    }
}

std::string SavingAccount::CreateAccount(int user_id,
                                  std::string account_holder,
                                  double amount, double rate) {
    //int user_id = user.getUserId();
    SavingAccount newAcc(user_id, account_holder, generateAccountNumber(user_id), amount, rate);

    return newAcc.getAccountNumber();
}
