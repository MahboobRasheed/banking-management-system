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
#include <iostream>
#include <string>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

class Node {
private:
    string firstName;
    string lastName;
    string cnic;
    int age;
    string gender;
    string phoneNumber;
    long int accountNumber;
    int pin;
    float balance;
    stack<string> transactionHistory; // Stack for transaction history
    Node* left;
    Node* right;

public:
    void createAccount();
    void addAccount();
    void deleteAccount(long int);
    void searchAccount(long int);
    void editAccount(long int);
    void depositAmount(long int);
    void withdrawAmount(long int);
    void showTransactionHistory(long int);
    void showAllAccounts();
    void addTransaction(const string&);
    void atmService(long int);
    int atmMenu();
    bool validatePin(long int, int);
    void printAccountDetails();
    static bool validateStaffPassword(const string&);
};

// Global head pointer for linked list
Node* head = NULL;
string staffPassword = "admin123"; // Predefined password for staff menu
// Function to create a new account
void Node::createAccount() {
    cout << "\n********** Create Account **********\n";
    cout << "Enter your First Name: ";
    cin >> firstName;
    cout << "Enter your Last Name: ";
    cin >> lastName;
    cout << "Enter your CNIC (13 digits): ";
    cin >> cnic;
    while (cnic.length() != 13) {
        cout << "Invalid CNIC. Enter again (13 digits): ";
        cin >> cnic;
    }
    cout << "Enter your Age: ";
    cin >> age;
    while (age < 18) {
        cout << "Age must be 18 or older. Enter again: ";
        cin >> age;
    }
    cout << "Enter your Gender (Male/Female): ";
    cin >> gender;
    transform(gender.begin(), gender.end(), gender.begin(), ::tolower);
    while (gender != "male" && gender != "female") {
        cout << "Invalid gender. Enter again (Male/Female): ";
        cin >> gender;
        transform(gender.begin(), gender.end(), gender.begin(), ::tolower);
    }
    cout << "Enter your Phone Number: +92 ";
    cin >> phoneNumber;
    while (phoneNumber.length() != 10) {
        cout << "Invalid phone number. Enter again (10 digits): +92 ";
        cin >> phoneNumber;
    }
    cout << "Enter initial deposit (minimum 500): ";
    cin >> balance;
    while (balance < 500) {
        cout << "Initial deposit must be at least 500. Enter again: ";
        cin >> balance;
    }
    
    srand(time(0));
    accountNumber = rand() % 9000000000000000 + 1000000000000000;
    cout << "Your Account Number: " << accountNumber << endl;

    // Take user's PIN as input (4-digit PIN)
    cout << "Enter a 4-digit PIN for your account: ";
    cin >> pin;
    while (pin < 1000 || pin > 9999) {
        cout << "PIN must be a 4-digit number. Enter again: ";
        cin >> pin;
    }

    transactionHistory.push("Account created with balance: " + to_string(balance));
    addAccount();
}

// Add the account to the linked list
void Node::addAccount() {
    Node* newNode = new Node();
    newNode->firstName = firstName;
    newNode->lastName = lastName;
    newNode->cnic = cnic;
    newNode->age = age;
    newNode->gender = gender;
    newNode->phoneNumber = phoneNumber;
    newNode->accountNumber = accountNumber;
    newNode->pin = pin;
    newNode->balance = balance;
    newNode->transactionHistory = transactionHistory;
    newNode->left = NULL;
    newNode->right = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->right != NULL) {
            temp = temp->right;
        }
        temp->right = newNode;
        newNode->left = temp;
    }
    cout << "Account created successfully!\n";
}

// Add a transaction to the account's transaction history
void Node::addTransaction(const string& transaction) {
    transactionHistory.push(transaction);
}

// Validate PIN
bool Node::validatePin(long int accNumber, int enteredPin) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->accountNumber == accNumber) {
            if (temp->pin == enteredPin) {
                return true;
            } else {
                cout << "Incorrect PIN entered.\n";
                return false;
            }
        }
        temp = temp->right;
    }
    cout << "Account not found.\n";
    return false;
}

// ATM Service Menu
void Node::atmService(long int accNumber) {
    int enteredPin;
    cout << "Enter your PIN: ";
    cin >> enteredPin;

    if (!validatePin(accNumber, enteredPin)) {
        return;
    }

    Node* temp = head;
    while (temp != NULL) {
        if (temp->accountNumber == accNumber) {
            cout << "\nATM Service:\n";
            cout << "1. Transaction Slip\n";  // Transaction history
            cout << "2. Withdraw\n";
            cout << "3. Check Balance\n";
            cout << "4. Cancel\n";
            int choice;
            cout << "Enter choice: ";
            cin >> choice;
            switch (choice) {
                case 1: {
                    // Transaction Slip: Show the last transaction
                    if (!temp->transactionHistory.empty()) {
                        cout << "\n********** Transaction Slip **********\n";
                        cout << "Latest Transaction: " << temp->transactionHistory.top() << endl;
                        cout << "***************************************\n";
                    } else {
                        cout << "No transaction history available.\n";
                    }
                    break;
                }
                case 2: {
                    int amount;
                    cout << "Enter amount to withdraw: ";
                    cin >> amount;
                    if (temp->balance - amount < 500) {
                        cout << "Insufficient funds! Withdrawal failed.\n";
                    } else {
                        temp->balance -= amount;
                        cout << "Withdrawal successful. New balance: " << temp->balance << endl;
                        temp->addTransaction("Withdrew: " + to_string(amount));
                    }
                    break;
                }
                case 3:
                    cout << "Current balance: " << temp->balance << endl;
                    break;
                case 4:
                    cout << "ATM session ended.\n";
                    break;
                default:
                    cout << "Invalid choice.\n";
            }
            return;
        }
        temp = temp->right;
    }
}

// Deposit Amount - Customer Menu
void Node::depositAmount(long int accNumber) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->accountNumber == accNumber) {
            int amount;
            cout << "Enter amount to deposit: ";
            cin >> amount;
            if (amount < 0) {
                cout << "Deposit amount must be greater than zero.\n";
                return;
            }
            temp->balance += amount;
            cout << "Deposit successful. New balance: " << temp->balance << endl;
            temp->addTransaction("Deposited: " + to_string(amount));
            return;
        }
        temp = temp->right;
    }
    cout << "Account not found.\n";
}

// Withdraw Amount - Customer Menu
void Node::withdrawAmount(long int accNumber) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->accountNumber == accNumber) {
            int amount;
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            if (amount < 0) {
                cout << "Withdrawal amount must be greater than zero.\n";
                return;
            }
            if (temp->balance - amount < 500) {
                cout << "Insufficient funds! Withdrawal failed.\n";
            } else {
                temp->balance -= amount;
                cout << "Withdrawal successful. New balance: " << temp->balance << endl;
                temp->addTransaction("Withdrew: " + to_string(amount));
            }
            return;
        }
        temp = temp->right;
    }
    cout << "Account not found.\n";
}

// Show transaction history for a specific account
void Node::showTransactionHistory(long int accNumber) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->accountNumber == accNumber) {
            if (!temp->transactionHistory.empty()) {
                cout << "\n********** Transaction History **********\n";
                stack<string> tempHistory = temp->transactionHistory;
                while (!tempHistory.empty()) {
                    cout << tempHistory.top() << endl;
                    tempHistory.pop();
                }
                cout << "***************************************\n";
            } else {
                cout << "No transaction history available.\n";
            }
            return;
        }
        temp = temp->right;
    }
    cout << "Account not found.\n";
}

// Search Account - Staff Menu
void Node::searchAccount(long int accNumber) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->accountNumber == accNumber) {
            cout << "\nAccount Found:\n";
            temp->printAccountDetails();
            return;
        }
        temp = temp->right;
    }
    cout << "Account not found.\n";
}

// Delete Account - Staff Menu
void Node::deleteAccount(long int accNumber) {
    Node* temp = head;
    Node* prev = NULL;
    while (temp != NULL) {
        if (temp->accountNumber == accNumber) {
            if (prev == NULL) { // Deleting the first node
                head = temp->right;
                if (head != NULL) {
                    head->left = NULL;
                }
            } else {
                prev->right = temp->right;
                if (temp->right != NULL) {
                    temp->right->left = prev;
                }
            }
            delete temp;
            cout << "Account deleted successfully.\n";
            return;
        }
        prev = temp;
        temp = temp->right;
    }
    cout << "Account not found.\n";
}