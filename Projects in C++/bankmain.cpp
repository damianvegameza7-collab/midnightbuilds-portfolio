#include <iostream>
#include <string>
#include "bankheader.hpp"
using namespace std;
void printMenu() {
    cout << "\n  ╔══════════════════════════════╗\n";
    cout << "  ║         BANKING SYSTEM     ║\n";
    cout << "  ╠══════════════════════════════╣\n";
    cout << "  ║  1. Create Account           ║\n";
    cout << "  ║  2. Deposit                  ║\n";
    cout << "  ║  3. Withdraw                 ║\n";
    cout << "  ║  4. Check Balance            ║\n";
    cout << "  ║  5. Transaction History      ║\n";
    cout << "  ║  6. View All Accounts        ║\n";
    cout << "  ║  7. Exit                     ║\n";
    cout << "  ╚══════════════════════════════╝\n";
    cout << "  Option: ";
}

int main() {
    Bank bank;
    int option;

    while(true) {
        printMenu();
        cin >> option;
        //Creates account for user
        if(option == 1) {
            string name;
            double intialDeposit;
        cout << "\n Enter your name: ";
        cin.ignore();
        getline(cin, name);
            cout <<"Intial deposit amount: $";
            cin >> intialDeposit;
        if(intialDeposit < 0) {
            cout <<"Intial deposit cannot be negative.\n";
        } else {
            bank.createAccount(name, intialDeposit);
        }
        //Bank deposit block
        } else if(option == 2) {
            int accNum;
            double amount;
            cout <<"\n Enter account number: ";
            cin >> accNum;
            bankAccount * acc = bank.findAccount(accNum);

            if(!acc) {
                cout <<"Account not found.\n";
            } else {
                cout <<" Deposit amount: $";
                cin >> amount;
                if(amount <= 0)
                cout <<" Amount must be greater than 0.\n";
            else
                acc->deposit(amount);             
            }
            //Withdraw bank option
        } else if (option == 3) {
            int accNum;
            double amount;
            cout <<"\n Enter account number: ";
            cin >> accNum;
        bankAccount * acc = bank.findAccount(accNum);
            if(!acc) {
                cout <<"Account not found.\n";

            } else {
                cout <<" Withdrawal amount: $";
                cin >> amount;
                if(amount <= 0)
                cout <<" Account must be greater than zero.\n";
            else
            acc->withdraw(amount);
            }
            //Checks balance for account/accounts
        } else if(option == 4){
            int accNum;
            cout << "\n Enter account number: ";
            cin >> accNum;
            bankAccount* acc = bank.findAccount(accNum);

            if(!acc) {
                cout <<"Account not found.\n";
            } else {
                cout << fixed;
                cout <<"\n Account #" << accNum << " (" << acc->getUserName()
                <<") " << "  | Balance: $" << acc->getBalance() << "\n";
            }
            //Transactions history
        } else if(option == 5) {
            int accNum;
            cout <<"\n Enter account number: ";
            cin >> accNum;
            bankAccount* acc = bank.findAccount(accNum);
                if(!acc)
                    cout<<"Account not found.\n";
                else 
                acc->printHistory();
                //View all accounts
        } else if(option == 6) {
            bank.printAllAccounts();
            //Exits program
        } else if(option == 7) {
            cout <<"\n Goodbye, have a great rest of your day!\n\n";
            break;
        } else {
            cout <<"Invalid option. Enter 1-7.\n";
        }
        }
        return 0;
    }