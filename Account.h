#pragma once
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Account {
protected:
    string cardNumber;
    string shabaNumber;
    string accountNumber;
    string cvv2;
    double balance;
    time_t expirationDate;
    string firstPassword;
    string fixedSecondPassword;
    string dynamicSecondPassword;
    string ownerNationalCode;

public:
    Account(const string& nationalCode, double initialBalance,
        const string& firstPass, const string& fixedSecondPass);
    virtual ~Account() {}

    virtual void showAccountType() const = 0;
    virtual void applyAccountRules() const = 0;

    string getCardNumber() const { return cardNumber; }
    string getOwnerNationalCode() const { return ownerNationalCode; }
    double getBalance() const { return balance; }
    bool checkExpiration() const;
    bool verifyFirstPassword(const string& input) const;
    bool verifyFixedSecondPassword(const string& input) const;
    bool verifyDynamicPassword(const string& input);
    void changeFirstPassword(const string& newPass);
    void changeFixedSecondPassword(const string& newPass);
    void generateDynamicPassword();
    void deposit(double amount);
    bool withdraw(double amount, const string& secondPassword);
};