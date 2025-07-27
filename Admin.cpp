#include "Admin.h"
#include "Customer.h"
#include "Account.h"
#include "DepositAccount.h"
#include "CurrentAccount.h"
#include "QardAlHasanaAccount.h"
#include <iostream>
#include <string>

using namespace std;

void Admin::showMenu() {
    int choice;
    do {
        cout << "\nAdmin Menu:\n"
            << "1. View all users\n"
            << "2. View all accounts\n"
            << "3. Add customer\n"
            << "4. Delete customer\n"
            << "5. View other admins\n"
            << "6. Change user information\n"
            << "7. Create account for customer\n"
            << "8. View specific account\n"
            << "9. Change password\n"
            << "0. Logout\n"
            << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: viewAllUsers(); break;
        case 2: viewAllAccounts(); break;
        case 3: addCustomer(); break;
        case 4: deleteCustomer(); break;
        case 5: viewOtherAdmins(); break;
        case 6: changeUserInfo(); break;
        case 7: createAccountForCustomer(); break;
        case 8: viewSpecificAccount(); break;
        case 9: changePassword(); break;
        case 0: return;
        default: cout << "Invalid choice!\n";
        }
    } while (true);
}

void Admin::viewAllUsers() const {
    for (int i = 0; i < allUsers->getSize(); i++) {
        User* user = *(allUsers->getAt(i));
        cout << "Name: " << user->getFullName() << "\n";
        cout << "Type: " << (user->isAdmin() ? "Admin" : "Customer") << "\n";
        cout << "National Code: " << user->getNationalCode() << "\n\n";
    }
}

void Admin::viewAllAccounts() const {
    
    cout << "All accounts viewing functionality\n";
}

void Admin::addCustomer() {
    User* newUser = User::createUser("customer");
    allUsers->add(newUser);
    cout << "Customer added successfully!\n";
}

void Admin::deleteCustomer() {
    string ncode;
    cout << "Enter customer national code: ";
    cin >> ncode;

    for (int i = 0; i < allUsers->getSize(); i++) {
        User* user = *(allUsers->getAt(i));
        if (!user->isAdmin() && user->getNationalCode() == ncode) {
            allUsers->remove(user);
            delete user;
            cout << "Customer deleted successfully!\n";
            return;
        }
    }
    cout << "Customer not found!\n";
}

void Admin::viewOtherAdmins() const {
    for (int i = 0; i < allUsers->getSize(); i++) {
        User* user = *(allUsers->getAt(i));
        if (user->isAdmin() && user != this) {
            cout << "Admin: " << user->getFullName() << "\n";
        }
    }
}

void Admin::changeUserInfo() {
    string ncode;
    cout << "Enter user national code: ";
    cin >> ncode;

    for (int i = 0; i < allUsers->getSize(); i++) {
        User* user = *(allUsers->getAt(i));
        if (user->getNationalCode() == ncode) {
            string newPass;
            cout << "Enter new password for user: ";
            cin >> newPass;
            
            cout << "Password changed successfully!\n";
            return;
        }
    }
    cout << "User not found!\n";
}

void Admin::createAccountForCustomer() {
    string ncode;
    cout << "Enter customer national code: ";
    cin >> ncode;

    Customer* customer = nullptr;
    for (int i = 0; i < allUsers->getSize(); i++) {
        User* user = *(allUsers->getAt(i));
        if (!user->isAdmin() && user->getNationalCode() == ncode) {
            customer = static_cast<Customer*>(user);
            break;
        }
    }

    if (!customer) {
        cout << "Customer not found!\n";
        return;
    }

    int type;
    double balance;
    string firstPass, secondPass;

    cout << "Account types:\n"
         << "1. Deposit\n"
         << "2. Current\n"
         << "3.Qard al - Hasana\n";

    cout << "Select account type: ";
    cin >> type;

    cout << "Enter initial balance: ";
    cin >> balance;

    cout << "Enter first password (4 digits): ";
    cin >> firstPass;

    cout << "Enter fixed second password: ";
    cin >> secondPass;

    Account* newAccount = nullptr;
    switch (type) {
    case 1:
        newAccount = new DepositAccount(ncode, balance, firstPass, secondPass);
        cout << "created account sacsfuly witw card number : " << newAccount->getCardNumber() << endl;
        break;
    case 2:
        newAccount = new CurrentAccount(ncode, balance, firstPass, secondPass);
        cout << "created account sacsfuly witw card number : " << newAccount->getCardNumber() << endl;
        break;
    case 3:
        newAccount = new QardAlHasanaAccount(ncode, balance, firstPass, secondPass);
        cout << "created account sacsfuly witw card number : " << newAccount->getCardNumber() << endl;
        break;
    default:
        cout << "Invalid account type!\n";
        return;
    }

    if (customer->addAccount(newAccount)) {
        cout << "Account created successfully!\n";
    }
    else {
        cout << "Customer already has 5 accounts!\n";
        delete newAccount;
    }
}

void Admin::viewSpecificAccount() const {
    string cardNumber;
    cout << "Enter card number: ";
    cin >> cardNumber;
    
    cout << "Account details functionality\n";
}