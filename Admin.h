#pragma once
#include "User.h"
#include <iostream>
#include <string>

using namespace std;

class Admin : public User {
public:
    Admin(const string& fname, const string& lname,
        const string& ncode, int age,
        const string& uname, const string& pass)
        : User(fname, lname, ncode, age, uname, pass) {}

    bool isAdmin() const override { return true; }
    void showMenu() override;

private:
    void viewAllUsers() const;
    void viewAllAccounts() const;
    void addCustomer();
    void deleteCustomer();
    void viewOtherAdmins() const;
    void changeUserInfo();
    void createAccountForCustomer();
    void viewSpecificAccount() const;
};