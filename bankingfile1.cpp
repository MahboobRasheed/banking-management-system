//MY 3rd SEMESTER PROJECT IN DSA SUBJECT IN DSA//
//IMPLEMENT DSA CONCEPT STACK IN TRANSECTION HISTORY//
#include <iostream>
#include <string>
#include <stack>
#include <ctime>
#include <iomanip>
#include <algorithm>
using namespace std;

// Utility Class
class Utility {
public:
    static string getCurrentDateTime() {
        time_t now = time(0);
        return string(ctime(&now));
    }
};

// Validation Class
class Validation {
public:
    static bool isValidCNIC(const string& cnic) {
        return cnic.length() == 13 && all_of(cnic.begin(), cnic.end(), ::isdigit);
    }

    static bool isValidPIN(int pin) {
        return pin >= 1000 && pin <= 9999;
    }
};

// Transaction Class
class Transaction {
public:
    string details;
    float amount;
    string date;

    Transaction(string details, float amount)
        : details(details), amount(amount), date(Utility::getCurrentDateTime()) {}
};

// TransactionHistory Class
class TransactionHistory {
    stack<Transaction> history;
public:
    void addTransaction(string details, float amount) {
        history.push(Transaction(details, amount));
    }

    void showHistory() {
        if (history.empty()) {
            cout << "No transaction history available.\n";
            return;
        }

        stack<Transaction> temp = history;
        cout << "\nTransaction History:\n";
        while (!temp.empty()) {
            Transaction t = temp.top();
            temp.pop();
            cout << "Details: " << t.details << ", Amount: " << t.amount << ", Date: " << t.date;
        }
    }
};

// Loan Class
class Loan {
public:
    float loanAmount;
    float loanBalance;
    float interestRate;
    string loanDetails;

    Loan(float loanAmount, float interestRate)
        : loanAmount(loanAmount), loanBalance(loanAmount), interestRate(interestRate) {
        loanDetails = "Loan Amount: " + to_string(loanAmount) + ", Interest Rate: " + to_string(interestRate) + "%";
    }

    void makeRepayment(float amount) {
        if (amount > loanBalance) {
            cout << "Repayment exceeds loan balance!\n";
            return;
        }
        loanBalance -= amount;
        cout << "Repayment of " << amount << " successful. Remaining loan balance: " << loanBalance << "\n";
    }
};

// Investment Class
class Investment {
public:
    float investmentAmount;
    string investmentType;

    Investment(float investmentAmount, string investmentType)
        : investmentAmount(investmentAmount), investmentType(investmentType) {}

    void showInvestmentDetails() {
        cout << "Investment Amount: " << investmentAmount << ", Investment Type: " << investmentType << endl;
    }
};

// Account Class
class Account {
public:
    string cnic, firstName, lastName, accountType;
    int age, pin;
    float balance;
    TransactionHistory transactionHistory;
    Loan* loan;
    Investment* investment;

    Account(string firstName, string lastName, string cnic, int age, string accountType, float balance, int pin)
        : firstName(firstName), lastName(lastName), cnic(cnic), age(age), accountType(accountType), balance(balance), pin(pin), loan(nullptr), investment(nullptr) {}

    void deposit(float amount) {
        balance += amount;
        transactionHistory.addTransaction("Deposit", amount);
        cout << "Deposit successful! Balance: " << balance << "\n";
    }

    void withdraw(float amount) {
        if (amount > balance) {
            cout << "Insufficient balance!\n";
            return;
        }
        balance -= amount;
        transactionHistory.addTransaction("Withdrawal", -amount);
        cout << "Withdrawal successful! Balance: " << balance << "\n";
    }

    void applyForLoan(float amount, float interestRate) {
        loan = new Loan(amount, interestRate);
        cout << "Loan applied successfully! Loan details: " << loan->loanDetails << "\n";
    }

    void makeLoanRepayment(float amount) {
        if (loan) {
            loan->makeRepayment(amount);
        } else {
            cout << "No loan found!\n";
        }
    }

    void startInvestment(float amount, string type) {
        investment = new Investment(amount, type);
        cout << "Investment started! Investment details: ";
        investment->showInvestmentDetails();
    }

    void viewLoanDetails() {
        if (loan) {
            cout << "Loan Details: " << loan->loanDetails << "\n";
        } else {
            cout << "No loan found!\n";
        }
    }

    void viewInvestmentDetails() {
        if (investment) {
            investment->showInvestmentDetails();
        } else {
            cout << "No investment found!\n";
        }
    }
};

#include <iostream>
#include <string>
#include <ctime>
#include <cctype>
#include <algorithm>

using namespace std;

struct TransactionNode {
    string transaction;
    TransactionNode* next;
};

class Account {
private:
    string firstName;
    string lastName;
    string cnic;
    string phoneNumber;
    int age;
    string accountType;
    long int accountNumber;
    int pin;
    float balance;
    TransactionNode* transactionHead;

public:
    Account(string firstName, string lastName, string cnic, string phoneNumber, int age, string accountType, float balance, int pin);
    ~Account();
    void depositAmount(float amount);
    bool withdrawAmount(float amount);
    void displayAccountDetails() const;
    void showTransactionHistory() const;
    bool validatePin(int inputPin) const;
    float getBalance() const { return balance; }
    long int getAccountNumber() const { return accountNumber; }
};

bool isValidName(const string &name) {
    return all_of(name.begin(), name.end(), [](char c) {
        return isalpha(c) || isspace(c); // Allow letters and spaces only
    });
}

bool isValidCnic(const string &cnic) {
    return cnic.length() == 13 && all_of(cnic.begin(), cnic.end(), ::isdigit);
}

bool isValidPhoneNumber(const string &phone) {
    return phone.length() == 10 && all_of(phone.begin(), phone.end(), ::isdigit);
}

Account::Account(string firstName, string lastName, string cnic, string phoneNumber, int age, string accountType, float balance, int pin)
    : firstName(firstName), lastName(lastName), cnic(cnic), phoneNumber(phoneNumber), age(age), accountType(accountType), balance(balance), pin(pin), transactionHead(nullptr) {
    
    srand(time(0));
    accountNumber = 10000000 + rand() % 90000000;

    cout << "\nAccount created successfully!" << endl;
    cout << "Account Number: " << accountNumber << endl;
    cout << "PIN: " << pin << endl;

    TransactionNode* newTransaction = new TransactionNode;
    newTransaction->transaction = "Account opened with balance: " + to_string(balance);
    newTransaction->next = nullptr;
    transactionHead = newTransaction;
}

Account::~Account() {
    TransactionNode* current = transactionHead;
    while (current != nullptr) {
        TransactionNode* next = current->next;
        delete current;
        current = next;
    }
}
