#include <iostream>
#include <exception>
#include <string>

using namespace std;

class BankingException : public exception {
protected:
    string message;

public:
    BankingException(string msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class InsufficientFundsException : public BankingException {
public:
    InsufficientFundsException(string msg) : BankingException(msg) {}
};

class InvalidAmountException : public BankingException {
public:
    InvalidAmountException(string msg) : BankingException(msg) {}
};

class BankAccount {
private:
    int accountNumber;
    double balance;

public:
    BankAccount(int accNo, double initialBalance) {
        accountNumber = accNo;
        balance = initialBalance;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            throw InvalidAmountException("Deposit amount must be positive.");
        }
        balance += amount;
        cout << "Successfully deposited: " << amount << ", New Balance: " << balance << endl;
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            throw InvalidAmountException("Withdrawal amount must be positive.");
        }
        if (amount > balance) {
            throw InsufficientFundsException("Insufficient funds for this withdrawal.");
        }
        balance -= amount;
        cout << "Successfully withdrew: " << amount << ", New Balance: " << balance << endl;
    }

    double getBalance() const {
        return balance;
    }
};

int main() {
    BankAccount account(101, 1000.0);

    try {
        cout << "Attempting valid deposit of 500:" << endl;
        account.deposit(500.0);

        cout << "Attempting valid withdrawal of 300:" << endl;
        account.withdraw(300.0);
    } catch (const BankingException& e) {
        cout << "Exception: " << e.what() << endl;
    }

    try {
        cout << endl << "Attempting invalid deposit of -100:" << endl;
        account.deposit(-100.0);
    } catch (const InvalidAmountException& e) {
        cout << "Caught InvalidAmountException: " << e.what() << endl;
    } catch (const BankingException& e) {
        cout << "Caught BankingException: " << e.what() << endl;
    }

    try {
        cout << endl << "Attempting withdrawal of 5000 (exceeds balance):" << endl;
        account.withdraw(5000.0);
    } catch (const InsufficientFundsException& e) {
        cout << "Caught InsufficientFundsException: " << e.what() << endl;
    } catch (const BankingException& e) {
        cout << "Caught BankingException: " << e.what() << endl;
    }

    return 0;
}
