#include <iostream>
#include <string>

using namespace std;

class BankAccount {
private:
    int accountNumber;

protected:
    string accountHolder;
    double balance;

public:
    BankAccount(int accNo, string name, double initialBalance) {
        accountNumber = accNo;
        accountHolder = name;
        balance = initialBalance;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: " << amount << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawn: " << amount << endl;
        } else {
            cout << "Insufficient funds or invalid amount" << endl;
        }
    }

    void display() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Holder Name: " << accountHolder << endl;
        cout << "Balance: " << balance << endl;
    }
};

class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(int accNo, string name, double initialBalance, double rate)
        : BankAccount(accNo, name, initialBalance) {
        interestRate = rate;
    }

    void addInterest() {
        double interest = balance * (interestRate / 100);
        balance += interest;
        cout << "Interest added: " << interest << endl;
    }

    void displaySavings() const {
        display();
        cout << "Interest Rate: " << interestRate << "%" << endl;
    }
};

int main() {
    SavingsAccount sa(1001, "Alice", 5000.0, 5.0);

    sa.displaySavings();

    sa.deposit(1500.0);
    sa.addInterest();
    sa.withdraw(2000.0);

    cout << endl << "Updated Account Details:" << endl;
    sa.displaySavings();

    return 0;
}
