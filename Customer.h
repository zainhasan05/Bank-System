#pragma once
#include "User.h"
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Customer : public User {
private:
    double dailyTransferred;
    time_t lastTransferDate;

public:
    Customer(const string& fname, const string& lname,
        const string& ncode, int age,
        const string& uname, const string& pass);

    bool isAdmin() const override { return false; }
    void showMenu() override;
    bool cardToCard(Account* fromAccount, Account* toAccount,
        double amount, const string& secondPassword);

private:
    void viewSpecificAccount() const;
    void changeAccountPassword();
    void cardToCardTransfer();
    void resetDailyTransfer();
};