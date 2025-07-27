#include "CurrentAccount.h"
#include <iostream>

using namespace std;

void CurrentAccount::showAccountType() const {
    cout << "Account Type: Current/Checking\n";
}

void CurrentAccount::applyAccountRules() const {
    cout << "Rules: No interest, unlimited transactions\n";
}