#include "User.h"
#include "Admin.h"
#include "Customer.h"
#include "Account.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    LinkedList<User*> allUsers;
    User::setUserList(&allUsers);

    
    Admin* defaultAdmin = new Admin("Admin", "User", "1234567890", 35, "admin", "admin123");
    allUsers.add(defaultAdmin);

    Customer* defaultCustomer = new Customer("John", "Doe", "0987654321", 30, "john", "password");
    allUsers.add(defaultCustomer);

    
    while (true) {
       cout << "\nBanking System\n"
            << "1. Login\n"
            << "2. Get Account\n"
            << "3. Exit\n"
            << "Choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            string username, password;
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;

            User* user = User::login(username, password);
            if (user) {
                user->showMenu();
            }
            else {
                cout << "Invalid credentials!\n";
            }
        }
        else if (choice == 2) {
            string Fname, Lname, N_ID, username, password;
            int Age;

            cout << "enter your firste name: ";
            cin.ignore();
            getline(cin, Fname);
            cout << "enter your last name: ";
            getline(cin, Lname);
            cout << "enter your phone number: ";
            getline(cin, N_ID);
            cout << "enter your age:";
            cin >> Age;
            cin.ignore();
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;

            Customer* defaultCustomer = new Customer(Fname, Lname, N_ID, Age, username, password);
            allUsers.add(defaultCustomer);

            cout << "\nnow youe have a profile with user name : " << username;
            cout << "\n\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "Invalid choice!\n";
        }
    }

    
    for (int i = 0; i < allUsers.getSize(); i++) {
        delete allUsers.getAt(i);
    }
    return 0;
}