#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Account {
protected:
    int accountNumber;
    string name;
    double balance;

public:
    Account(int accNo, string accName, double initialBalance) {
        accountNumber = accNo;
        name = accName;
        balance = initialBalance;
    }

    virtual ~Account() {}

    virtual void withdraw(double amount) = 0;

    void deposit(double amount) {
        balance += amount;
        cout << "Amount deposited successfully. New balance: Rs." << balance << "\n";
    }

    virtual void display() {
        cout << "A/C No: " << accountNumber << " | Name: " << name << " | Balance: Rs." << balance << "\n";
    }

    int getAccountNumber() {
        return accountNumber;
    }

    string getName() {
        return name;
    }

    double getBalance() {
        return balance;
    }
};

class SavingsAccount : public Account {
public:
    SavingsAccount(int accNo, string accName, double initialBalance) : Account(accNo, accName, initialBalance) {}

    void withdraw(double amount) override {
        if (balance - amount < 500) {
            cout << "Transaction failed. Minimum balance of Rs.500 must be maintained.\n";
        } else {
            balance -= amount;
            cout << "Amount withdrawn successfully. New balance: Rs." << balance << "\n";
        }
    }

    void display() override {
        cout << "[Savings] ";
        Account::display();
    }
};

class Bank {
private:
    vector<Account*> accounts;

public:
    ~Bank() {
        for (size_t i = 0; i < accounts.size(); i++) {
            delete accounts[i];
        }
    }

    void createAccount(Account* acc) {
        accounts.push_back(acc);
        cout << "Account created successfully!\n";
    }

    void displayAll() {
        if (accounts.empty()) {
            cout << "No accounts found.\n";
            return;
        }
        cout << "\n--- Bank Accounts ---\n";
        for (size_t i = 0; i < accounts.size(); i++) {
            accounts[i]->display();
        }
    }

    void performTransaction(int accNo, int type) {
        for (size_t i = 0; i < accounts.size(); i++) {
            if (accounts[i]->getAccountNumber() == accNo) {
                double amount;
                if (type == 1) {
                    cout << "Enter amount to deposit: ";
                    cin >> amount;
                    accounts[i]->deposit(amount);
                } else if (type == 2) {
                    cout << "Enter amount to withdraw: ";
                    cin >> amount;
                    accounts[i]->withdraw(amount);
                }
                return;
            }
        }
        cout << "Account not found.\n";
    }

    void saveToFile() {
        ofstream file("bank_data.txt");
        if (!file) {
            cout << "Error opening file!\n";
            return;
        }
        for (size_t i = 0; i < accounts.size(); i++) {
            file << accounts[i]->getAccountNumber() << " "
                 << accounts[i]->getName() << " "
                 << accounts[i]->getBalance() << "\n";
        }
        file.close();
        cout << "Bank data saved to bank_data.txt!\n";
    }
};

int main() {
    Bank myBank;
    int choice = 0;

    while (true) {
        cout << "\n1. Open Savings Account\n2. Deposit Money\n3. Withdraw Money\n4. Display All Accounts\n5. Save and Exit\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int accNo;
            string name;
            double initBal;
            cout << "Enter Account No, Name, and Initial Balance (space separated): ";
            cin >> accNo >> name >> initBal;
            myBank.createAccount(new SavingsAccount(accNo, name, initBal));
        }
        else if (choice == 2) {
            int accNo;
            cout << "Enter Account Number: ";
            cin >> accNo;
            myBank.performTransaction(accNo, 1);
        }
        else if (choice == 3) {
            int accNo;
            cout << "Enter Account Number: ";
            cin >> accNo;
            myBank.performTransaction(accNo, 2);
        }
        else if (choice == 4) {
            myBank.displayAll();
        }
        else if (choice == 5) {
            myBank.saveToFile();
            cout << "Exiting system...\n";
            break;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}
