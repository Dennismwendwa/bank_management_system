#include "bank_ops.hpp"
#include "bank_account.h"
#include "utils.hpp"

Bank::Bank(std::shared_ptr<IStorage> storage) : storage(std::move(storage)) {
    
}

bool Bank::openAccount(int userId, const std::string& holderName, double initialDeposit, std::string national_id, double interestRate) {
    SavingAccount account = SavingAccount::CreateAccount(userId, holderName, initialDeposit, national_id, interestRate);
    cout << "\n\nNational ID\nid: " << account.getNationalId() << endl;

    if (storage->getStorageType() == "File") {
        
    }

    std::string transaction_type = "deposit";
    std::string currency = "KSH";
    std::string description = "Opening account deposit";
    std::string status = "Completed";
    std::string method = "Bank";
    Transaction newTrans = Transaction::createTransaction(generateTransactionID(), getCurrentDayTime(), transaction_type,
                         account.getAccountHolder(), account.getBalance(), currency,
                         description, status, method, account.getAccountNumber());
    storage->saveTransaction(newTrans);
    return storage->saveAccount(account);

}

std::optional<SavingAccount> Bank::getAccountById(int id) {
    return storage->findAccountById(id);
}

void Bank::recordTransaction(const std::string& type, const SavingAccount& account, double amount, const std::string& description) {
    std::string currency = "KSH";
    std::string status = "Completed";
    std::string method = "Bank";

    Transaction trans = Transaction::createTransaction(
        generateTransactionID(), getCurrentDayTime(), type,
        account.getAccountHolder(), amount, currency,
        description, status, method, account.getAccountNumber());

    storage->saveTransaction(trans);

    Ledger new_ledger = Ledger::createLedger(trans, account.getAccountHolder(), currency, getCurrentDayTime());
    
    cout << "\n\nTransaction ddetail " << trans.getAmount() << endl;
    //new_ledger.printAll();
    cout << "\n\n";
    
    storage->saveLedger(new_ledger);
}

void Bank::recordTransaction(std::string transaction_id, const std::string& type,
                             const SavingAccount& account,
                             double amount, 
                             const std::string& description,
                             const SavingAccount& from_account) {
    std::string currency = "KSH";
    std::string status = "Completed";
    std::string method = "Bank";

    Transaction trans = Transaction::createTransaction(
        transaction_id, getCurrentDayTime(), type,
        account.getAccountHolder(), amount, currency,
        description, status, method, account.getAccountNumber(), 
        from_account.getAccountNumber()
    );

    storage->saveTransaction(trans);

    Ledger new_ledger = Ledger::createLedger(trans, account.getAccountHolder(), currency, getCurrentDayTime());
    cout << "\n\nTransaction ddetail " << trans.getAmount() << endl;
    //new_ledger.printAll();
    cout << "\n\n";
    storage->saveLedger(new_ledger);
}

void Bank::saveUpdatedAccount(const SavingAccount& account) {
    storage->saveAccount(account);
}

bool Bank::withdraw(std::string account_number, double amount) {
    std::optional<SavingAccount> account = storage->findAccountByAccountNumber(account_number);

    if (account && amount > 0) {
        account->withdraw(amount);
        saveUpdatedAccount(*account);
        recordTransaction("withdraw", *account, amount, "Withdrawal of money");
        return true;
    }
    return false;
}

bool Bank::deposit(std::string account_number, std::string id_number, double amount) {
    std::optional<SavingAccount> account = storage->findAccountByAccountNumber(account_number);

    if (!account) {
        return false;
    }

    if (account->getNationalId() != id_number) {
        std::cerr << "Error: Provided ID does not match account owner.\n";
        return false;
    }

    if (amount > 0) {
        account->deposit(amount);
        saveUpdatedAccount(*account);
        recordTransaction("deposit", *account, amount, "Deposit of money");
        return true;
    }
    return false;
}

bool Bank::transfer(std::string id_number, std::string from_account_number, std::string to_account_number, double amount) {
    std::optional<SavingAccount> from_account = storage->findAccountByAccountNumber(from_account_number);
    std::optional<SavingAccount> to_account = storage->findAccountByAccountNumber(to_account_number);

    if (!from_account || !to_account) {
        return false;
    }

    if (from_account->getNationalId() != id_number) {
        std::cerr << "Error: Provided ID does not match account owner.\n";
        return false;
    }

    if (amount > 0) {
        from_account->transfer(*to_account, amount);

        saveUpdatedAccount(*from_account);
        saveUpdatedAccount(*to_account);

        std::string transaction_id = generateTransactionID();
        recordTransaction(transaction_id, "transfer_out", *from_account, amount, "Transfer of money to another account", *to_account);
        recordTransaction(transaction_id, "transfer_in", *to_account, amount, "Transfer of money received", *from_account);

        return true;
    }
    return false;
}
