#include "Account.h"
#include "Encryption.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <conio.h>
#include <unistd.h>

using namespace std;

// simple helper to ensure PIN contains only digits, no letters or symbols
bool isNumericPin(const string& pin) {
    for (char c : pin) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// small CLI loading effect just for UI feel
void processing() {
    cout << "Processing";
    for (int i = 0; i < 3; i++) {
        cout << ".";
        cout.flush();
        sleep(1);
    }
    cout << endl;
}

// handles PIN input and hides characters using '*'
string Account::getHiddenInput() {
    string input = "";
    char ch;

    // reads input character by character until Enter is pressed
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') { // handle backspace properly
            if (!input.empty()) {
                input.pop_back();
                cout << "\b \b";
            }
        } else {
            input.push_back(ch);
            cout << '*'; // mask actual digits
        }
    }

    cout << endl;
    return input;
}

// creates a new user account and stores it in file
void Account::createAccount() {

    cout << "Enter username: ";
    getline(cin >> ws, username);

    cout << "Enter password: ";
    getline(cin >> ws, password);

    cout << "Enter transaction PIN (4 digits): ";
    pin = getHiddenInput();

    // validate PIN format before saving
    while (!isNumericPin(pin) || pin.length() != 4) {
        cout << "Invalid PIN! Try again: ";
        pin = getHiddenInput();
    }

    cout << "Enter initial balance: ";
    cin >> balance;

    // encrypt sensitive data before saving
    password = Encryption::hash(password);
    pin = Encryption::hash(pin);

    ofstream file("users.txt", ios::app);

    // store user in simple pipe separated format
    file << username << "|" << password << "|" << pin << "|" << balance << endl;

    processing();
    cout << "Account created successfully!\n";
}

// login system checks file for matching credentials
bool Account::login(string inputUser, string inputPass) {

    ifstream file("users.txt");

    string line, fileUser, filePass, filePin;
    double fileBalance;

    string hashedInput = Encryption::hash(inputPass);

    // read database line by line
    while (getline(file, line)) {

        stringstream ss(line);

        getline(ss, fileUser, '|');
        getline(ss, filePass, '|');
        getline(ss, filePin, '|');
        ss >> fileBalance;

        if (fileUser == inputUser && filePass == hashedInput) {

            // load user data into current session
            username = fileUser;
            password = filePass;
            pin = filePin;
            balance = fileBalance;

            processing();
            cout << "Login successful!\n";

            return true;
        }
    }

    return false;
}

// verifies PIN by comparing hashed values
bool Account::verifyPin(string inputPin) {
    return Encryption::hash(inputPin) == pin;
}

// withdraw money after PIN validation
void Account::withdraw(double amount, string inputPin) {

    if (Encryption::hash(inputPin) == pin) {

        processing();

        if (amount <= balance) {
            balance -= amount;
            updateFile();
            cout << "Withdrawal successful\n";
        } else {
            cout << "Insufficient balance\n";
        }

    } else {
        cout << "Incorrect PIN\n";
    }
}

// deposit funds into account
void Account::deposit(double amount) {

    processing();

    balance += amount;
    updateFile();
    cout << "Deposit successful\n";
}

// display account balance after PIN check
void Account::viewBalance(string inputPin) {

    if (Encryption::hash(inputPin) == pin) {

        processing();
        cout << "Balance: " << fixed << setprecision(2) << balance << endl;

    } else {
        cout << "Incorrect PIN\n";
    }
}

// updates only the modified user's record in file
void Account::updateFile() {

    ifstream inFile("users.txt");
    ofstream outFile("temp.txt");

    string line, fileUser, filePass, filePin;
    double fileBalance;

    // rewrite file safely using temp file method
    while (getline(inFile, line)) {

        stringstream ss(line);

        getline(ss, fileUser, '|');
        getline(ss, filePass, '|');
        getline(ss, filePin, '|');
        ss >> fileBalance;

        if (fileUser == username) {
            outFile << username << "|" << password << "|" << pin << "|" << balance << endl;
        } else {
            outFile << line << endl;
        }
    }

    inFile.close();
    outFile.close();

    remove("users.txt");
    rename("temp.txt", "users.txt");
}