#include "json_storage.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

JSONStorage::JSONStorage(const std::string& filename) : filename(filename) {}

bool JSONStorage::saveAccount(const SavingAccount& account) {
    std::lock_guard<std::mutex> lock(fileMutex);

    SavingAccount modifiableAccount = account;

    cout << "\nStorage save\n";
    auto accounts = loadAllAccounts();
    int next_id = getNextAccountID(accounts);
    modifiableAccount.setAccountId(next_id);

    accounts.push_back(modifiableAccount);
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