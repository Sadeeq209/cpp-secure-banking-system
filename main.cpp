#include <iostream>
#include "Account.h"

using namespace std;

int main() {

    int choice;
    Account acc;

    do {

        // main menu loop (keeps program running until exit)
        cout << "\n*************************\n";
        cout << "   BANK SYSTEM MENU   \n";
        cout << "*************************\n";
        cout << "1. Create Account\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "*************************\n";
        cout << "Enter choice: ";

        cin >> choice;

        // handle invalid numeric input (prevents crash)
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (choice == 1) {
            // create new user account
            acc.createAccount();
        }

        else if (choice == 2) {

            string user, pass;
            bool success = false;

            // allow up to 3 login attempts
            for (int attempts = 0; attempts < 3; attempts++) {

                cout << "Enter username: ";
                cin >> ws;
                getline(cin, user);

                cout << "Enter password: ";
                getline(cin, pass);

                // check credentials against stored data
                if (acc.login(user, pass)) {
                    success = true;
                    break;
                }

                cout << "Wrong credentials\n";
            }

            // only enter account menu if login succeeds
            if (success) {

                int option;

                do {

                    // account menu after login
                    cout << "\n*************************\n";
                    cout << "   ACCOUNT MENU   \n";
                    cout << "*************************\n";
                    cout << "1. View Balance\n";
                    cout << "2. Deposit\n";
                    cout << "3. Withdraw\n";
                    cout << "4. Logout\n";
                    cout << "*************************\n";
                    cout << "Enter choice: ";

                    cin >> option;

                    // validate menu input
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        continue;
                    }

                    if (option == 1) {

                        string pin;
                        bool ok = false;

                        // allow 3 attempts for PIN verification
                        for (int i = 0; i < 3; i++) {

                            cout << "Enter transaction PIN: ";
                            pin = acc.getHiddenInput();

                            if (acc.verifyPin(pin)) {
                                acc.viewBalance(pin);
                                ok = true;
                                break;
                            }

                            cout << "Incorrect PIN\n";
                        }

                        if (!ok) {
                            cout << "PIN blocked\n";
                        }
                    }

                    else if (option == 2) {

                        double amount;
                        cout << "Enter amount: ";
                        cin >> amount;

                        // deposit money into account
                        acc.deposit(amount);
                    }

                    else if (option == 3) {

                        double amount;
                        string pin;

                        cout << "Enter amount: ";
                        cin >> amount;

                        cout << "Enter PIN: ";
                        pin = acc.getHiddenInput();

                        // withdraw money after PIN check
                        acc.withdraw(amount, pin);
                    }

                    else if (option == 4) {
                        cout << "Logging out...\n";
                    }

                    else {
                        cout << "Invalid option\n";
                    }

                } while (option != 4);
            }
        }

        else if (choice == 3) {
            cout << "Exiting...\n";
        }

        else {
            cout << "Invalid choice\n";
        }

    } while (choice != 3);

    return 0;
}