#include "bankheader.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

bankAccount:: bankAccount(string name, int accountNum, double intialDeposit)
: userName(name), accountNumber(accountNum), balance(0) {
    deposit(intialDeposit);
}

int bankAccount::getAccountNumber() const {
    return accountNumber;
}
string bankAccount::getUserName() const {
    return userName;
}
double bankAccount:: getBalance() const {
    return balance;
}

void bankAccount::deposit(double amount) {
    balance+= amount;
    history.push_back({"Deposit" , amount, balance });
    cout << fixed << setprecision(2);
    cout <<" Deposited $ " << amount << " | " << "New balance: $" << balance << endl;
}

bool bankAccount::withdraw (double amount) {
    if(amount > balance) {
        cout <<"Insufficient funds. Current balance: $" << fixed << setprecision(2)
        << balance << endl;
        return false;
    }
    balance -= amount;
    history.push_back({"Withdrawal" , amount, balance});
    cout << fixed << setprecision(2);
    cout << " Withdrew $" << amount <<"  | New Balance: $" << balance << endl;
    return true;
}
    void bankAccount::printHistory() const {
        cout <<"\n Transaction history for account #" << accountNumber << " (" << userName
        << ")\n";
        cout << " " << string(50, '-') << "\n";
        cout << left << setw(14) << " Type" << setw(12)
        << "Amount" << setw(16) << "Balance after" << "\n";
        cout << " " << string(50, '-') << "\n";

    if (history.empty()) {
        cout <<"No transactions yet. \n";
    } else {
        for (const auto& t : history) {
             cout << fixed << setprecision(2);
            cout << left << setw(14) << ("  " + t.type)
                 << setw(12) << ("$" + to_string(t.amount).substr(0, to_string(t.amount).find('.') + 3))
                 << ("$" + to_string(t.balanceAfter).substr(0, to_string(t.balanceAfter).find('.') + 3))
                 << "\n";
        }
    }
    cout << "  " << string(50, '-') << "\n";
}
    void bankAccount::printSummary() const {
        cout << fixed << setprecision(2);
        cout <<" Account #" << accountNumber <<"  | Owner: " << userName
        << "  | Balance: $" << balance << "\n";
    }
        Bank::Bank() : nextAccountNumber(1001) {}
        void Bank::createAccount(string name, double intialDeposit) {
            accounts.emplace_back(name, nextAccountNumber++, intialDeposit);
            cout <<"Account created succesfully! " << "Account number: " 
            << (nextAccountNumber - 1) << "\n";
    }
        bankAccount*Bank::findAccount(int accountNumber) {
            for(auto& acc : accounts) {
                if(acc.getAccountNumber() == accountNumber)
                return &acc;
            }
            return nullptr;
        }
        void Bank::printAllAccounts() const {
            if(accounts.empty()) {
                cout << " No accounts found. \n";
                return;
            }
            cout <<"\n " << string(50, '-') << "\n";
                for(const auto& acc : accounts)
                acc.printSummary();
            cout <<"\n " << string(50, '-') << "\n";
        }