#include "User.h"
#include "Admin.h"
#include "Customer.h"
#include "Account.h"
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

LinkedList<User*>* User::allUsers = nullptr;

User::User(const string& fname, const string& lname,
    const string& ncode, int age,
    const string& uname, const string& pass)
    : firstName(fname), lastName(lname), nationalCode(ncode),
    age(age), username(uname), password(pass) {}

User* User::login(const string& uname, const string& pass) {
    for (int i = 0; i < allUsers->getSize(); i++) {
        User* user = *(allUsers->getAt(i));
        if (user->username == uname && user->password == pass) {
            return user;
        }
    }
    return nullptr;
}

User* User::createUser(const string& type) {
    string fname, lname, ncode, uname, pass;
    int age;

    cout << "Enter first name: ";
    cin >> fname;
    cout << "Enter last name: ";
    cin >> lname;
    cout << "Enter national code: ";
    cin >> ncode;
    cout << "Enter age: ";
    cin >> age;
    cout << "Enter username: ";
    cin >> uname;
    cout << "Enter password: ";
    cin >> pass;

    if (type == "admin") {
        return new Admin(fname, lname, ncode, age, uname, pass);
    }
    else {
        return new Customer(fname, lname, ncode, age, uname, pass);
    }
}

void User::viewAllAccounts() const {
    for (int i = 0; i < accounts.getSize(); i++) {
        Account* acc = *(accounts.getAt(i));
        cout << "Account " << (i + 1) << ":\n";
        acc->showAccountType();
        cout << "Card Number: " << acc->getCardNumber() << "\n";
        cout << "Balance: " << acc->getBalance() << " Tomans\n\n";
    }
}

Account* User::findAccount(const string& cardNumber) const {
    for (int i = 0; i < accounts.getSize(); i++) {
        Account* acc = *(accounts.getAt(i));

        if (acc->getCardNumber() == cardNumber) {
            return acc;
        }
    }
    return nullptr;
}

bool User::addAccount(Account* account) {
    if (accounts.getSize() >= 5) return false;
    accounts.add(account);
    return true;
}

bool User::removeAccount(const string& cardNumber) {
    for (int i = 0; i < accounts.getSize(); i++) {
        Account* acc = *(accounts.getAt(i));
        if (acc->getCardNumber() == cardNumber) {
            accounts.remove(acc);
            return true;
        }
    }
    return false;
}

void User::changePassword() {
    string newPass;
    cout << "Enter new password: ";
    cin >> newPass;
    password = newPass;
    cout << "Password changed successfully!\n";
}
