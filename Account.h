#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

// represents a single bank account and all its operations
class Account {
private:
    std::string username;
    std::string password;
    std::string pin;
    double balance;

public:
    // creates a new account and saves it to file
    void createAccount();

    // handles user login verification
    bool login(std::string inputUser, std::string inputPass);

    // checks if entered PIN matches stored PIN
    bool verifyPin(std::string inputPin);

    // deposit money into account balance
    void deposit(double amount);

    // withdraw money after PIN validation
    void withdraw(double amount, std::string inputPin);

    // displays current account balance
    void viewBalance(std::string inputPin);

    // updates user data inside the database file
    void updateFile();

    // gets PIN input with masking (****)
    std::string getHiddenInput();
};

#endif