#include "json_storage.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

JSONStorage::JSONStorage(const std::string& filename) : filename(filename) {}

bool JSONStorage::saveAccount(const SavingAccount& account) {
    std::lock_guard<std::mutex> lock(fileMutex);

    auto accounts = loadAllAccounts();
    bool found = false;
    
    for (auto& acc : accounts) {
        if (acc.getAccountNumber() == account.getAccountNumber()) {
            acc = account;
            found = true;
            break;
        }
    }

    if (!found) {
        SavingAccount modifiableAccount = account;
        int next_id = getNextAccountID(accounts);
        modifiableAccount.setAccountId(next_id);
        accounts.push_back(modifiableAccount);
    }
    
    writeAllAccounts(accounts);
    return true;
}

std::optional<SavingAccount> JSONStorage::findAccountById(int id) {
    std::lock_guard<std::mutex> lock(fileMutex);

    auto accounts = loadAllAccounts();
    for (const auto& acc : accounts) {
        if (acc.getAccountId() == id) {
            return acc;
        }
    }
    return std::nullopt;
}

std::optional<SavingAccount> JSONStorage::findAccountByAccountNumber(const std::string& account_number)
{
    std::lock_guard<std::mutex> lock(fileMutex);

    auto accounts = loadAllAccounts();
    for (const auto& acc : accounts) {
        if (acc.getAccountNumber() == account_number) {
            return acc;
        }
    }
    return std::nullopt;
}

std::vector<SavingAccount> JSONStorage::loadAllAccounts() {
    std::ifstream inFile(filename);
    std::vector<SavingAccount> accounts;

    if (!inFile.is_open()) return accounts;

        json data;
        inFile >> data;

    for (auto& item : data) {
        SavingAccount acc(
            item["account_id"],
            item["user_id"],
            item["account_holder"],
            item["account_number"],
            item["balance"],
            item["nationl_id"],
            item["interest_rate"],
            item["minimum_balance"],
            item["monthly_withdrawals"],
            item["max_withdrawals"],
            item["account_type"],
            item["created_on"]
        );
        accounts.push_back(acc);
    }
    return accounts;
}

void JSONStorage::writeAllAccounts(const std::vector<SavingAccount>& accounts) {
    std::ofstream outFile(filename);
    json j = json::array();

    for (const auto& acc : accounts) {
        j.push_back({
            {"account_id", acc.getAccountId()},
            {"user_id", acc.getUserId()},
            {"account_holder", acc.getAccountHolder()},
            {"account_number", acc.getAccountNumber()},
            {"balance", acc.getBalance()},
            {"nationl_id", acc.getNationalId()},
            {"interest_rate", acc.getInterestRate()},
            {"minimum_balance", acc.getMinimumBalance()},
            {"monthly_withdrawals", acc.getMonthlyWithdrawals()},
            {"max_withdrawals", acc.getMaxWithdrawals()},
            {"account_type", acc.getAccountType()},
            {"created_on", acc.getCreatedOn()}
        });
    }
    outFile << j.dump(4);
}

int JSONStorage::getNextAccountID(const std::vector<SavingAccount>& accounts) {
    //std::vector<SavingAccount> accounts = loadAllAccounts();
    int max_id = 0;
    for (const auto& acc : accounts) {
        if (acc.getAccountId() > max_id) {
            max_id = acc.getAccountId();
        }
    }
    return max_id + 1;
}


/**
 * Transaction funcs
 * 
 * 
 */
int JSONStorage::getNextTransactionID(const std::vector<Transaction>& transactions) {
    //std::vector<SavingAccount> accounts = loadAllAccounts();
    int max_id = 0;
    
    for (const auto& acc : transactions) {
        int pk = acc.getPrimaryKey();
        if (pk > max_id) {
            max_id = pk;
        }
    }
    return max_id + 1;
}

json to_json(const Transaction& t) {
    json j;
    j["id"] = t.getPrimaryKey();
    j["transaction_id"] = t.getTransactionId();
    j["date_time"] = t.getDatetime();
    j["transaction_type"] = t.getTransactionType();
    j["account_holder"] = t.getAccountHolder();
    j["amount"] = t.getAmount();
    j["currency"] = t.getCurrency();
    j["description"] = t.getDescription();
    j["status"] = t.getStatus();
    j["method"] = t.getMethod();
    j["source_account"] = t.getSourceAccount().value_or("");
    j["destination_account"] = t.getDestinationAccount().has_value() ? t.getDestinationAccount().value() : "";
    return j;
}

Transaction from_json(const json& j) {
    return Transaction(
        j.at("id"),
        j.at("transaction_id"),
        j.at("date_time"),
        j.at("transaction_type"),
        j.at("account_holder"),
        j.at("amount"),
        j.at("currency"),
        j.at("description"),
        j.at("status"),
        j.at("method"),
        j.at("source_account"),
        j.at("destination_account").get<std::string>().empty() ? std::nullopt : std::make_optional(j.at("destination_account").get<std::string>())
    );
}

bool JSONStorage::saveTransaction(const Transaction& transaction) {
    std::lock_guard<std::mutex> lock(fileMutex);
    std::vector<Transaction> transactions = loadAllTransactions();

    int next_id = getNextTransactionID(transactions);

    Transaction transaction_copy = transaction;
    transaction_copy.setPrimaryKey(next_id);
    cout << transaction_copy.getPrimaryKey() << endl;
    transactions.push_back(transaction_copy);
    writeAllTransactions(transactions);
    return true;
}

std::vector<Transaction> JSONStorage::getAllTransactions() {
    std::lock_guard<std::mutex> lock(fileMutex);
    return loadAllTransactions();
}

std::vector<Transaction> JSONStorage::loadAllTransactions() {
    std::ifstream inFile(filename);
    std::vector<Transaction> transactions;

    if (inFile) {
        json j;
        inFile >> j;
        for (const auto& item : j) {
            transactions.push_back(from_json(item));
        }
    }
    return transactions;
}

void JSONStorage::writeAllTransactions(const std::vector<Transaction>& transaction) {
    std::ofstream outFile(filename);
    json j = json::array();
    for (const auto& t : transaction) {
        j.push_back(to_json(t));
    }
    outFile << j.dump(4);
}
