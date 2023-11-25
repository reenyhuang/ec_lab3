#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Account {
    public:
        Account(const string& accNum, const string& accHolder, double balance)
            : accNum(accNum), accHolder(accHolder), balance(balance) {}

        virtual void displayDetails(ostream& os) const
        {
            os << "     Account Holder: " << accHolder << endl;
            os << "     Balance: $" << fixed << setprecision(2) << balance << endl;
        }

        void deposit(double amount)
        {
            if (amount > 0)
            {
                balance += amount;
            }
            else
            {
                cout << "Invalid deposit amount. Amount must be greater than 0." << endl;
            }
        }

        virtual void withdraw(double amount)
        {
            if (amount > 0 && balance >= amount)
            {
                balance -= amount;
            }
            else
            {
                cout << "Invalid withdrawa; amount or insufficient funds.";
            }
        }

    friend ostream& operator<<(ostream& os, const Account& account)
        {
            account.displayDetails(os);
            return os;
        }
    // transfer a set 25 dollars from account b to a
    friend void operator+(Account& a, Account& b)
        {
            a.balance += 25;
            b.balance -= 25;
        }

    protected:
        string accNum;
        string accHolder;
        double balance;
};


class SavingsAccount : public Account
{
    public:
        SavingsAccount(const string& accNum, const string& accHolder, double balance, double interestRate)
            : Account(accNum, accHolder, balance), interestRate(interestRate) {}

        void withdraw(double amount) override
        {
            if (amount > 0 && balance - amount >= minBalance) 
            {
                balance -= amount;
            } 
            else 
            {
                cout << "Invalid withdrawal amount, insufficient funds, or below minimum balance of $25." << endl;
            }
        }

        void displayDetails(ostream& os) const override 
        {
            os << "Account Details for Savings Account (ID: " << accNum << "):" << endl;
            Account::displayDetails(os);
            os << "     Interest Rate: " << fixed << setprecision(2) << (interestRate * 100) << "%" << endl;
        }

    private:
        double interestRate;
        inline static constexpr double minBalance = 25.0;
};


class CurrentAccount : public Account
{
    public:
        CurrentAccount(const string& accNumber, const string& accHolder, double balance, double overdraftLimit)
        : Account(accNumber, accHolder, balance), overdraftLimit(overdraftLimit) {}

        void withdraw(double amount) override 
        {
            if (amount > 0 && balance - amount >= -overdraftLimit)
            {
                balance -= amount;
            } 
            else
            {
                cout << "Invalid withdrawal amount or overdraft limit reached." << endl;
            }
        }

        void displayDetails(ostream& os) const override 
        {
            os << "Account Details for Current Account (ID: " << accNum << "):" << endl;
            Account::displayDetails(os);
            os << "     Overdraft Limit: " << fixed << setprecision(2) << overdraftLimit << endl;
        }

    private:
        double overdraftLimit;
};

int main()
{
    SavingsAccount savings("S123", "John Doe", 1000, 0.02);
    CurrentAccount current("C456", "Jane Doe", 2000, 500);
    cout << "Initial account details: \n";
    cout << savings<<"\n";
    cout << current;

    //demonstrating deposit and withdrawal operations
    savings.deposit(500);
    cout << "\nAccount details after $500 deposit: \n";
    cout << savings;

    savings.withdraw(200);
    cout << "\nAccount details after $200 withdraw: \n";
    cout << savings;
    //demonstrating deposit and withdrawal operations
    current.deposit(1000);
    cout << "\nAccount details after $1000 deposit: \n";
    cout << current;

    current.withdraw(500);
    cout << "\nAccount details after $500 withdraw: \n";
    cout << current;

    // Transfer 25 from savings to current
    cout << "\nAccount details after transferring $25 from savings to current: \n";
    current + savings;
    savings.displayDetails(cout);
    current.displayDetails(cout);

    return 0;
}
