#pragma once
#include "LinkedList.h"
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Account;

class User {
protected:
    string firstName;
    string lastName;
    string nationalCode;
    int age;
    string username;
    string password;
    LinkedList<Account*> accounts;
    static LinkedList<User*>* allUsers;

public:
    User(const std::string& fname, const std::string& lname,
        const std::string& ncode, int age,
        const std::string& uname, const std::string& pass);
    virtual ~User() {}

    static void setUserList(LinkedList<User*>* list) { allUsers = list; }
    static User* login(const string& uname, const string& pass);
    static User* createUser(const string& type);

    virtual bool isAdmin() const = 0;
    std::string getNationalCode() const { return nationalCode; }
    std::string getFullName() const { return firstName + " " + lastName; }
    void viewAllAccounts() const;
    Account* findAccount(const string& cardNumber) const;
    bool addAccount(Account* account);
    bool removeAccount(const string& cardNumber);
    void changePassword();
    virtual void showMenu() = 0;
};