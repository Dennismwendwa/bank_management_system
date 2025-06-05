#include "accounts/helper.hpp"

void updateMonthlyWithdrawals(User& user) {
    if (user.monthly_withdrawals > 0) {
        user.monthly_withdrawals--;
    }
}