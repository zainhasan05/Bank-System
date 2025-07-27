#include "Customer.h"
#include "Account.h"
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

Customer::Customer(const string& fname, const string& lname,
    const string& ncode, int age,
    const string& uname, const string& pass)
    : User(fname, lname, ncode, age, uname, pass),
    dailyTransferred(0) {
    time(&lastTransferDate);
}

void Customer::showMenu() {
    resetDailyTransfer();
    int choice;
    do {
       cout << "\nCustomer Menu:\n"
            << "1. View all accounts\n"
            << "2. View specific account\n"
            << "3. Change account password\n"
            << "4. Card to card transfer\n"
            << "5. Change user password\n"
            << "0. Logout\n"
            << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: viewAllAccounts(); break;
        case 2: viewSpecificAccount(); break;
        case 3: changeAccountPassword(); break;
        case 4: cardToCardTransfer(); break;
        case 5: changePassword(); break;
        case 0: return;
        default: cout << "Invalid choice!\n";
        }
    } while (true);
}

void Customer::viewSpecificAccount() const {
    string cardNumber;
    cout << "Enter card number: ";
    cin >> cardNumber;

    Account* acc = findAccount(cardNumber);
    if (acc) {
        cout << "Card Number: " << acc->getCardNumber() << "\n";
        cout << "Balance: " << acc->getBalance() << " Tomans\n";
        acc->showAccountType();
    }
    else {
        cout << "Account not found!\n";
    }
}

void Customer::changeAccountPassword() {
    string cardNumber, whichPass, newPass;
    cout << "Enter card number: ";
    cin >> cardNumber;

    Account* acc = findAccount(cardNumber);
    if (!acc) {
        cout << "Account not found!\n";
        return;
    }

    cout << "Change first or second password? (first/second): ";
    cin >> whichPass;
    cout << "Enter new password: ";
    cin >> newPass;
        if (whichPass == "first") {
        acc->changeFirstPassword(newPass);
    }
    else if (whichPass == "second") {
        acc->changeFixedSecondPassword(newPass);
    }
    else {
        cout << "Invalid choice!\n";
        return;
    }
    cout << "Password changed successfully!\n";
}

void Customer::cardToCardTransfer() {
    string fromCard, toCard, secondPass;
    double amount;

    cout << "Enter your card number: ";
    cin >> fromCard;
    Account* fromAccount = findAccount(fromCard);
    if (!fromAccount) {
        cout << "Account not found!\n";
        return;
    }

    cout << "Enter recipient card number: ";
    cin >> toCard;

    Account* toAccount = nullptr;
    cout << "Recipient: [Recipient Name]\n";

    cout << "Enter amount (Tomans): ";
    cin >> amount;

    cout << "Enter second password: ";
    cin >> secondPass;

    if (cardToCard(fromAccount, toAccount, amount, secondPass)) {
        cout << "Transfer successful!\n";
    }
    else {
        cout << "Transfer failed!\n";
    }
}

bool Customer::cardToCard(Account* fromAccount, Account* toAccount,
    double amount, const string& secondPassword) {
    
    if (dailyTransferred + amount > 6000000) {
        cout << "Exceeds daily transfer limit (6 million Tomans)!\n";
        return false;
    }

       if (amount > 3000000) {
        cout << "Exceeds per-transaction limit (3 million Tomans)!\n";
        return false;
       }

    if (!fromAccount->checkExpiration()) {
        cout << "Card expired!\n";
        return false;
    }

        if (amount <= 100000) {
        if (!fromAccount->verifyFixedSecondPassword(secondPassword)) {
            cout << "Invalid second password!\n";
            return false;
        }
    }
    else {
        if (!fromAccount->verifyDynamicPassword(secondPassword)) {
            cout << "Invalid or expired dynamic password!\n";
            return false;
        }
    }

    double fee = amount * 0.0001;
    double total = amount + fee;

        if (fromAccount->getBalance() < total) {
        cout << "Insufficient balance!\n";
        return false;
    }

    
    fromAccount->withdraw(total, secondPassword);
    toAccount->deposit(amount);
    dailyTransferred += amount;

        if (amount > 100000) {
        fromAccount->generateDynamicPassword();
        cout << "New dynamic password generated for future transactions.\n";
        }

    return true;
}

void Customer::resetDailyTransfer() {
    time_t now = time(nullptr);
    tm now_tm;
    localtime_s(&now_tm, &now);

    tm last_tm;
    localtime_s(&last_tm, &lastTransferDate);

    if (now_tm.tm_mday != last_tm.tm_mday ||
        now_tm.tm_mon != last_tm.tm_mon ||
        now_tm.tm_year != last_tm.tm_year) {
        dailyTransferred = 0;
        lastTransferDate = now;
    }

}