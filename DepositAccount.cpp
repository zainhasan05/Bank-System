#include "DepositAccount.h"
#include <iostream>

using namespace std;

void DepositAccount::showAccountType() const {
    cout << "Account Type: Deposit Savings\n";
}

void DepositAccount::applyAccountRules() const {
    cout << "Rules: Higher interest rates, limited withdrawals\n";
}