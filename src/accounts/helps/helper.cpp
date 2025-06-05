#include "accounts/helper.hpp"
#include "bank_account.h"


void updateMonthlyWithdrawals(SavingAccount& account) {
    int withdrawals{account.getMonthlyWithdrawals()};
    
    withdrawals++;
    
    account.setMonthlyWithdrawals(withdrawals);
}