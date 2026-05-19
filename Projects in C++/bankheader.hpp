#ifndef BANKHEADER_CPP
#define BANKHEADER_CPP

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Transaction{
    string type;
    double amount;
    double balanceAfter;
};

class bankAccount {
private:
    string userName;
    int accountNumber;
    double balance;
    vector <Transaction> history;

public:
    bankAccount(string name, int accNum, double intialDeposit);

    int getAccountNumber() const;
    string getUserName() const;
    double getBalance() const;

    void deposit(double amount);
    bool withdraw(double amount);
    void printHistory() const;
    void printSummary() const;
};

class Bank {
    private:
    vector<bankAccount> accounts;
    int nextAccountNumber;

public:
    Bank();
    void createAccount(string name, double intialDeposit);
    bankAccount * findAccount(int accountNumber);
    void printAllAccounts() const;
};

#endif