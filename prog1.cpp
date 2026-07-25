#include <iostream>
using namespace std;

class BankAccount
{
protected:
    int accountNumber;
    string accountHolderName;

private:
    double balance;

public:
    BankAccount() {}

    BankAccount(int accNo, string name, double bal)
    {
        accountNumber = accNo;
        accountHolderName = name;
        balance = bal;
    }

    void deposit(double amount)
    {
        balance=balance + amount;
        cout << "Amount Deposited Successfully.\n";
    }

    virtual void withdraw(double amount)
    {
        if (amount <= balance)
        {
            balance=balance - amount;
            cout << "Amount Withdrawn Successfully.\n";
        }
        else
        {
            cout << "Insufficient Balance.\n";
        }
    }

    double getBalance()
    {
        return balance;
    }

    void setBalance(double bal)
    {
        balance = bal;
    }

    virtual void calculateInterest()
    {
        cout << "Interest calculation is not available.\n";
    }

    virtual void displayAccountInfo()
    {
        cout << "\n------ Account Details ------\n";
        cout << "Account Number : " << accountNumber << endl;
        cout << "Account Holder : " << accountHolderName << endl;
        cout << "Balance        : " << getBalance() << endl;
    }

    virtual ~BankAccount() {}
};

class SavingsAccount : public BankAccount
{
private:
    double interestRate;

public:
    SavingsAccount(int accNo, string name, double bal, double rate)
        : BankAccount(accNo, name, bal)
    {
        interestRate = rate;
    }

    void calculateInterest()
    {
        double interest = getBalance() * interestRate / 100;
        cout << "Savings Interest = " << interest << endl;
    }
};

class CheckingAccount : public BankAccount
{
private:
    double overdraftLimit;

public:
    CheckingAccount(int accNo, string name, double bal, double limit)
        : BankAccount(accNo, name, bal)
    {
        overdraftLimit = limit;
    }

    void withdraw(double amount)
    {
        if (amount <= getBalance() + overdraftLimit)
        {
            setBalance(getBalance() - amount);
            cout << "Withdrawal Successful.\n";
        }
        else
        {
            cout << "Overdraft Limit Exceeded.\n";
        }
    }

    void calculateInterest()
    {
        cout << "Checking Account has no interest.\n";
    }
};

class FixedDepositAccount : public BankAccount
{
private:
    int term;
    double interestRate;

public:
    FixedDepositAccount(int accNo, string name, double bal, int t, double rate)
        : BankAccount(accNo, name, bal)
    {
        term = t;
        interestRate = rate;
    }

    void calculateInterest()
    {
        double interest = getBalance() * interestRate * term / (100 * 12);
        cout << "Fixed Deposit Interest = " << interest << endl;
    }
};

int main()
{
    SavingsAccount savings(101, "Nevil", 10000, 5);
    CheckingAccount checking(102, "Raj", 5000, 2000);
    FixedDepositAccount fd(103, "Pruthvi", 20000, 12, 7);

    BankAccount *account;

    int choice, type;
    double amount;

    while (true)
    {
        cout << "\n===== BANK MENU =====\n";
        cout << "1. Savings Account\n";
        cout << "2. Checking Account\n";
        cout << "3. Fixed Deposit Account\n";
        cout << "4. Exit\n";
        cout << "Enter Account Type: ";
        cin >> type;

        if (type == 4)
            break;

        if (type == 1)
            account = &savings;
        else if (type == 2)
            account = &checking;
        else if (type == 3)
            account = &fd;
        else
        {
            cout << "Invalid Account Type.\n";
            continue;
        }

        cout << "\n1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Display Account\n";
        cout << "4. Calculate Interest\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Amount: ";
            cin >> amount;
            account->deposit(amount);
            break;

        case 2:
            cout << "Enter Amount: ";
            cin >> amount;
            account->withdraw(amount);
            break;

        case 3:
            account->displayAccountInfo();
            break;

        case 4:
            account->calculateInterest();
            break;

        default:
            cout << "Invalid Choice.\n";
        }
    }

    cout << "\nThank You for Using Banking System.\n";

    return 0;
}
