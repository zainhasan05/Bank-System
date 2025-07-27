#pragma once
#include "Account.h"
#include <iostream>
#include <string>

using namespace std;

class QardAlHasanaAccount : public Account {
public:
    QardAlHasanaAccount(const string& nationalCode, double initialBalance,
        const string& firstPass, const string& fixedSecondPass)
        : Account(nationalCode, initialBalance, firstPass, fixedSecondPass) {}

    void showAccountType() const override;
    void applyAccountRules() const override;
};