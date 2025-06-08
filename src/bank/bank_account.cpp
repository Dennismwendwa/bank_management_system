#include "bank_account.h"
#include "user.h"
#include "utils.hpp"

BankAccount::BankAccount(int user_id, std::string ah, std::string an, std::string ID) {
    user_id = user_id, account_holder = ah, account_number = an, balance = 0, nationl_id = ID;
}

BankAccount::BankAccount(int ud, std::string ah, std::string an, double b, std::string ID) {
    const double MIN_BALANCE = 10000.0;

    if (b < MIN_BALANCE) {
        throw std::invalid_argument("Initial balance must be at least Ksh 10,000.");
    }
    user_id = ud,
    account_holder = ah;
    account_number = an;
    balance = b;
    nationl_id = ID;
}
BankAccount::BankAccount(int acc_id, int user_id, std::string ah, std::string an, double b, std::string ID)
    : account_id(acc_id), user_id(user_id), account_holder(ah), account_number(an), balance(b), nationl_id(ID) {}

void BankAccount::setAccountNumber(std::string new_number) {
    account_number = new_number;
}

std::string BankAccount::getAccountNumber() const {
    return account_number;
}

void BankAccount::setAccountHolder(std::string new_holder) {
    account_holder = new_holder;
}

std::string BankAccount::getAccountHolder() const {
    return account_holder;
}

void BankAccount::setBalance (double new_balance) {
    balance = new_balance;
}

void BankAccount::setNationalId(std::string new_id) {
    nationl_id = new_id;
}

double BankAccount::getBalance() const {
    return balance;
}

std::string BankAccount::getNationalId() const {
    return nationl_id;
}
void BankAccount::setAccountId(int new_id) {
    account_id = new_id;
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

SavingAccount::SavingAccount(int user_id,
                             std::string ah,
                             std::string an,
                             double b,
                             std::string ni,
                             double rate
        ) : BankAccount(user_id, ah, an, b, ni), created_on(getCurrentDate()), interest_rate(rate) {
        minimum_balance = 10000;
        monthly_withdrawals = 0;
        max_withdrawals = 3;
        account_type = "Basic";
    }
SavingAccount::SavingAccount(int account_id, int user_id, std::string account_holder,
                             std::string account_number, double balance, std::string ni, double interest_rate,
                             double minimum_balance, int monthly_withdrawals, int max_withdrawals,
                             std::string account_type, std::string created_on
                            ) : BankAccount(account_id, user_id, account_holder, account_number, balance, ni
                            ), created_on(created_on),
                            interest_rate(interest_rate),
                            minimum_balance(minimum_balance),
                            monthly_withdrawals(monthly_withdrawals),
                            max_withdrawals(max_withdrawals),
                            account_type(account_type) {}

std::string SavingAccount::getCurrentDate() const {
    std::time_t now = std::time(nullptr);
    std::tm* local_time = std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(local_time, "%Y-%m-%d");
    return oss.str();
}

void SavingAccount::setCreatedOn(std::string new_date) {
    created_on = new_date;
}
std::string SavingAccount::getCreatedOn() const {
    return created_on;
}

void SavingAccount::setInterestRate(double new_interest_rate) {
    interest_rate = new_interest_rate;                                                  
}

double SavingAccount::getInterestRate() const {
    return interest_rate;
}

void SavingAccount::setMinimumBalance(double new_balance) {
    minimum_balance = new_balance;
}

double SavingAccount::getMinimumBalance () const {
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

int SavingAccount::getMonthlyWithdrawals() const {
    return monthly_withdrawals;
}

void SavingAccount::setMaxWithdrawals(int new_max) {
    max_withdrawals = new_max;
}

int SavingAccount::getMaxWithdrawals() const {
    return max_withdrawals;
}

void SavingAccount::setAccountType(std::string new_type) {
    account_type = new_type;
}

std::string SavingAccount::getAccountType() const {
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

void SavingAccount::deposit(double amount) {
    if (amount > 0) {
        setBalance(getBalance() + amount);
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

SavingAccount SavingAccount::CreateAccount(int user_id,
                                  std::string account_holder,
                                  double amount, std::string national_id, double rate) {
    
    SavingAccount newAcc(user_id, account_holder, generateAccountNumber(user_id),
                         amount, national_id, rate);
    
    return newAcc;
}

/*
Transactions
*/

Transaction::Transaction(
                    std::string transaction_id,
                    std::string date_time,
                    std::string transaction_type,
                    std::string account_holder,
                    double amount,
                    std::string currency,
                    std::string description,
                    std::string status,
                    std::string method,
                    std::string source_account,
                    std::optional<std::string> destination_account
                    ) : transaction_id(transaction_id),
                    date_time(date_time),
                    transaction_type(transaction_type),
                    account_holder(account_holder),
                    amount(amount),
                    currency(currency),
                    description(description),
                    status(status),
                    method(method),
                    source_account(source_account),
                    destination_account(destination_account) {}

Transaction::Transaction(
                    int id, // primary key
                    std::string transaction_id,
                    std::string date_time,
                    std::string transaction_type,
                    std::string account_holder,
                    double amount,
                    std::string currency,
                    std::string description,
                    std::string status,
                    std::string method,
                    std::string source_account,
                    std::optional<std::string> destination_account
                    ) : id(id),
                    transaction_id(transaction_id),
                    date_time(date_time),
                    transaction_type(transaction_type),
                    account_holder(account_holder),
                    amount(amount),
                    currency(currency),
                    description(description),
                    status(status),
                    method(method),
                    source_account(source_account),
                    destination_account(destination_account) {}

void Transaction::setTransactionId(std::string new_transaction_id) { transaction_id = new_transaction_id; }
void Transaction::setDatetime(std::string new_date_time) { date_time = new_date_time; }
void Transaction::setTransactionType(std::string new_transaction_type) {transaction_type = new_transaction_type; }
void Transaction::setAccountHolder(std::string new_account_holder) {account_holder = new_account_holder; }
void Transaction::setSourceAccount(std::string new_source_account) { source_account = new_source_account; }
void Transaction::setDestinationAccount(std::string new_destination_account) { destination_account = new_destination_account; }
void Transaction::setamount(double new_amount) { amount = new_amount; }
void Transaction::setCurrency(std::string new_currency) { currency = new_currency; }
void Transaction::setDescription(std::string new_descriction) { description = new_descriction; }
void Transaction::setStatus(std::string new_status) { status = new_status; }
void Transaction::setMethod(std::string new_method) { method = new_method; }
void Transaction::setPrimaryKey(int new_id) { id = new_id; }
int Transaction::getPrimaryKey() const { return id; }
std::string Transaction::getTransactionId() const { return transaction_id; }
std::string Transaction::getDatetime() const { return date_time; }
std::string Transaction::getAccountHolder() const { return account_holder; }
std::optional<std::string> Transaction::getSourceAccount() const { return source_account; }
std::optional<std::string> Transaction::getDestinationAccount() const { return destination_account; }
double Transaction::getAmount() const { return amount; }
std::string Transaction::getCurrency() const { return currency; }
std::string Transaction::getDescription() const { return description; }
std::string Transaction::getStatus() const { return status; }
std::string Transaction::getMethod() const { return method; }
std::string Transaction::getTransactionType() const { return transaction_type; }

Transaction Transaction::createTransaction(
            const std::string& transaction_id, const std::string& date_time,
            const std::string& transaction_type, const std::string& account_holder,
            double amount, const std::string& currency, const std::string& description,
            const std::string& status, const std::string& method,
            const std::string source_account,
            std::optional<std::string> destination_account) {
        Transaction newTrans(transaction_id, date_time, transaction_type, account_holder,
                             amount, currency, description, status, method, source_account,
                            destination_account);
        
    return newTrans;
}

/**
Ledger
 */

Ledger::Ledger(const Transaction& t, std::string account_holder, std::string currency, std::string date
    ) : transaction(t), account_number(account_holder), date(date), currency(currency) {}
Ledger::Ledger(int id, const Transaction& t, std::string accountNumber, std::string currency, std::string date)
    : id(id), transaction(t), account_number(std::move(accountNumber)), currency(std::move(currency)), date(std::move(date)) {}


std::string Ledger::getAccountNumber() const { return account_number; }
std::string Ledger::getDate() const { return date; }
std::string Ledger::getCurrency() const { return currency; }
int Ledger::getPrimaryKey() const { return id; }
void Ledger::setPrimaryKey(int new_pk) { id = new_pk; }
const Transaction& Ledger::getTransaction() const {return transaction; }


Ledger Ledger::createLedger(
        const Transaction& transaction, const std::string& account_holder,
        const std::string& currency, const std::string& date ) {
            Ledger newLedger(transaction, account_holder, currency, date);
        return newLedger;
}

Ledger Ledger::createLedger(int id,
        const Transaction& transaction, const std::string& account_holder,
        const std::string& currency, const std::string& date ) {
            Ledger newLedger(id, transaction, account_holder, currency, date);
        return newLedger;
}

double Ledger::computeNetBalance() const {
    double balance = 0.0;

    return balance;
}

double Ledger::computeAccountBalance(const std::string& account) const {
    if (transaction.getAccountHolder() == account) {
        return transaction.getAmount();
    }
    return 0.0;
}

double Ledger::computeTotalByType(const std::string& type) const {
    double total = 0.0;
    
    return total;
}

void Ledger::printAll() const {
    std::cout << "All Transactions:\n";
    std::cout << "----------------------------------------------\n";
    Transaction t = getTransaction();

    std::cout << "ID: " << t.getTransactionId() << "\n";
    std::cout << "Date: " << t.getDatetime() << "\n";
    std::cout << "Type: " << t.getTransactionType() << "\n";
    std::cout << "From: " << (t.getSourceAccount().has_value() ? t.getSourceAccount().value() : "N/A") << "\n";
    std::cout << "To: " << (t.getDestinationAccount().has_value() ? t.getDestinationAccount().value() : "N/A") << "\n";
    std::cout << "Amount: " << t.getAmount() << " " << t.getCurrency() << "\n";
    std::cout << "Status: " << t.getStatus() << "\n";
    std::cout << "Method: " << t.getMethod() << "\n";
    std::cout << "Description: " << t.getDescription() << "\n";
    std::cout << "----------------------------------------------\n";

}
