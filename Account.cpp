#include "Account.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

Account::Account(const string& nationalCode, double initialBalance,
    const string& firstPass, const string& fixedSecondPass)
    : ownerNationalCode(nationalCode), balance(initialBalance),
    firstPassword(firstPass), fixedSecondPassword(fixedSecondPass) {
    
    srand(time(nullptr));
    cardNumber = to_string(rand() % 9000 + 1000) +
                 to_string(rand() % 9000 + 1000) +
                 to_string(rand() % 9000 + 1000) +
                 to_string(rand() % 9000 + 1000);

    
    time_t now = time(nullptr);
    expirationDate = now + (5 * 365 * 24 * 60 * 60);
}

bool Account::checkExpiration() const {
    return time(nullptr) <= expirationDate;
}

bool Account::verifyFirstPassword(const string& input) const {
    return input == firstPassword;
}

bool Account::verifyFixedSecondPassword(const string& input) const {
    return input == fixedSecondPassword;
}

bool Account::verifyDynamicPassword(const string& input) {
    if (input == dynamicSecondPassword) {
        dynamicSecondPassword = "";
        return true;
    }
    return false;
}

void Account::changeFirstPassword(const string& newPass) {
    firstPassword = newPass;
}

void Account::changeFixedSecondPassword(const string& newPass) {
    fixedSecondPassword = newPass;
}

void Account::generateDynamicPassword() {
    srand(time(nullptr));
    dynamicSecondPassword = to_string(rand() % 900000 + 100000);
}

void Account::deposit(double amount) {
    balance += amount;
}

bool Account::withdraw(double amount, const string& secondPassword) {
    if (balance >= amount) {
        balance -= amount;
        return true;
    }
    return false;
}
