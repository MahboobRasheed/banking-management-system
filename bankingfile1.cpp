//MY 3rd SEMESTER PROJECT IN DSA SUBJECT IN DSA//
//IMPLEMENT DSA CONCEPT STACK IN TRANSECTION HISTORY//
#include <iostream>
#include <string>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>

using namespace std;

class Node {
private:
    string firstName, lastName, cnic, gender, phoneNumber;
    int age;
    int pin;                   
    long long accountNumber;   
    float balance;
    stack<string> transactionHistory;
    Node* left;
    Node* right;

    static long long generateAccountNumber() {
        return (long long)(rand() % 9000000000000000 + 1000000000000000);
    }
    bool isAllDigits(const string& str) {
        for (char c : str) {
            if (!isdigit(c)) {
                return false;
            }
        }
        return true;
    }
    Node(string firstName, string lastName, string cnic, int age, string gender, string phoneNumber, float balance, int pin)
        : firstName(firstName), lastName(lastName), cnic(cnic), age(age), gender(gender),
          phoneNumber(phoneNumber), balance(balance), pin(pin),
          accountNumber(generateAccountNumber()), left(nullptr), right(nullptr) {
        transactionHistory.push("Account created with balance: " + to_string(balance));
    }

public:
    static Node* head; 
    static void createAccount();
    static void addAccount(Node*);
    static void depositAmount(long long);
    static void withdrawAmount(long long);
    static void showTransactionHistory(long long);
    static void investInSavings(long long);
    static void payBill(long long);
    static void showAllAccounts();
    static void searchAccount(long long);
    static void deleteAccount(long long);
    static void editAccount(long long);
    static bool validatePin(long long, int);
    static void atmService(long long);
    static void customerMenu();
    static void staffMenu();
    static void printAccountDetails(Node*);
};

Node* Node::head = nullptr; 

bool Node::validatePin(long long accNumber, int enteredPin) {
    Node* temp = Node::head;
    while (temp) {
        if (temp->accountNumber == accNumber) {
            return temp->pin == enteredPin; // Check if the entered PIN matches the stored PIN
        }
        temp = temp->right;
    }
    return false; // Return false if account not found
}

void Node::createAccount() {
    cout << "\n********** Create Account **********\n";

    string firstName, lastName, cnic, gender, phoneNumber;
    int age, pin;
    float balance;

    cout << "Enter First Name: ";
    cin >> firstName;
    cout << "Enter Last Name: ";
    cin >> lastName;

    cout << "Enter CNIC (13 digits): ";
    cin >> cnic;
    while (cnic.length() != 13) {
        cout << "Invalid CNIC. Enter again (13 digits): ";
        cin >> cnic;
    }

    cout << "Enter Age (18 or older): ";
    cin >> age;
    while (age < 18) {
        cout << "Age must be 18 or older. Enter again: ";
        cin >> age;
    }

    cout << "Enter Gender (Male/Female): ";
    cin >> gender;
    transform(gender.begin(), gender.end(), gender.begin(), ::tolower);
    while (gender != "male" && gender != "female") {
        cout << "Invalid Gender. Enter again (Male/Female): ";
        cin >> gender;
        transform(gender.begin(), gender.end(), gender.begin(), ::tolower);
    }

    cout << "Enter Phone Number (10 digits): +92 ";
    cin >> phoneNumber;
    while (phoneNumber.length() != 10) {
        cout << "Invalid Phone Number. Enter again (10 digits): +92 ";
        cin >> phoneNumber;
    }

    cout << "Enter Initial Deposit (minimum 500): ";
    cin >> balance;
    while (balance < 500) {
        cout << "Initial deposit must be at least 500. Enter again: ";
        cin >> balance;
    }

    cout << "Set a 4-digit PIN for your account: ";
    cin >> pin;
    while (pin < 1000 || pin > 9999) {
        cout << "PIN must be a 4-digit number. Enter again: ";
        cin >> pin;
    }

    Node* newNode = new Node(firstName, lastName, cnic, age, gender, phoneNumber, balance, pin);
    addAccount(newNode);

    cout << "Account created successfully! Your account number is: " << newNode->accountNumber << "\n";
}

void Node::addAccount(Node* newNode) {
    if (!head) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->right) {
            temp = temp->right;
        }
        temp->right = newNode;
        newNode->left = temp;
    }
}

void Node::depositAmount(long long accNumber) {
    Node* temp = head;
    while (temp) {
        if (temp->accountNumber == accNumber) {
            int amount;
            cout << "Enter amount to deposit: ";
            cin >> amount;
            if (amount <= 0) {
                cout << "Invalid amount!\n";
                return;
            }
            temp->balance += amount;
            temp->transactionHistory.push("Deposited: " + to_string(amount));
            cout << "Deposit successful. New balance: " << temp->balance << "\n";
            return;
        }
        temp = temp->right;
    }
    cout << "Account not found.\n";
}

void Node::withdrawAmount(long long accNumber) {
    Node* temp = head;
    while (temp) {
        if (temp->accountNumber == accNumber) {
            int amount;
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            if (amount <= 0 || amount > temp->balance - 500) {
                cout << "Invalid amount! Ensure a minimum balance of 500 remains.\n";
                return;
            }
            temp->balance -= amount;
            temp->transactionHistory.push("Withdrew: " + to_string(amount));
            cout << "Withdrawal successful. New balance: " << temp->balance << "\n";
            return;
        }
        temp = temp->right;
    }
    cout << "Account not found.\n";
}

void Node::showTransactionHistory(long long accNumber) {
    Node* temp = head;
    while (temp) {
        if (temp->accountNumber == accNumber) {
            if (temp->transactionHistory.empty()) {
                cout << "No transactions available.\n";
                return;
            }
            cout << "\n********** Transaction History **********\n";
            stack<string> history = temp->transactionHistory;
            while (!history.empty()) {
                cout << history.top() << endl;
                history.pop();
            }
            return;
        }
        temp = temp->right;
    }
    cout << "Account not found.\n";
}

void Node::investInSavings(long long accNumber) {
    Node* temp = head;
    while (temp) {
        if (temp->accountNumber == accNumber) {
            float amount;
            cout << "Enter amount to invest (minimum balance of 500 required): ";
            cin >> amount;

            if (amount <= 0 || temp->balance - amount < 500) {
                cout << "Invalid amount. Ensure you have at least 500 remaining balance.\n";
                return;
            }

            cout << "Select Investment Plan:\n";
            cout << "1. 1 Month (2% profit)\n";
            cout << "2. 6 Months (8% profit)\n";
            cout << "3. 1 Year (15% profit)\n";
            cout << "Enter your choice: ";
            int plan;
            cin >> plan;

            float profit = 0;
            switch (plan) {
                case 1:
                    profit = amount * 0.02;
                    break;
                case 2:
                    profit = amount * 0.08;
                    break;
                case 3:
                    profit = amount * 0.15;
                    break;
                default:
                    cout << "Invalid plan. Investment cancelled.\n";
                    return;
            }

            temp->balance -= amount;
            temp->transactionHistory.push("Invested " + to_string(amount) + " in savings");
            cout << "Investment successful! Expected profit: " << profit << "\n";
            return;
        }
        temp = temp->right;
    }
    cout << "Account not found.\n";
}

void Node::payBill(long long accNumber) {
    Node* temp = Node::head;
    while (temp) {
        // Use a public method or accessor to access accountNumber
        if (temp->accountNumber == accNumber) {
            cout << "Which type of bill would you like to pay?\n";
            cout << "1. Electricity\n";
            cout << "2. Water\n";
            int choice;
            cin >> choice;

            string billId;
            cout << "Enter Bill ID: ";
            cin >> billId;

            // Validate Bill ID length based on the bill type
            if (choice == 1) { // Electricity
                if (billId.length() != 14 || !temp->isAllDigits(billId)) {
                    cout << "Invalid electricity bill ID. It must be 14 digits.\n";
                    return;
                }
            } else if (choice == 2) { // Water
                if (billId.length() != 10 || !temp->isAllDigits(billId)) {
                    cout << "Invalid water bill ID. It must be 10 digits.\n";
                    return;
                }
            } else {
                cout << "Invalid bill type choice.\n";
                return;
            }

            // Ask for the bill amount
            cout << "Enter Bill Amount: ";
            float amount;
            cin >> amount;

            // Validate the amount (should leave at least 500 balance)
            if (amount <= 0 || amount > temp->balance - 500) {
                cout << "Invalid amount! Ensure a minimum balance of 500 remains.\n";
                return;
            }

            // Validate the PIN using the public method
            int attempts = 0;
            while (attempts < 3) {
                cout << "Enter PIN: ";
                int enteredPin;
                cin >> enteredPin;

                // Use the public validatePin method
                if (validatePin(accNumber, enteredPin)) {
                    // PIN is correct, process payment
                    temp->balance -= amount;
                    temp->transactionHistory.push("Paid bill ID: " + billId + " Amount: " + to_string(amount));
                    cout << "Bill payment successful. New balance: " << temp->balance << "\n";
                    return;
                } else {
                    cout << "Incorrect PIN. Try again.\n";
                    attempts++;
                }
            }

            cout << "Too many incorrect PIN attempts. Going back...\n";
            return;
        }
        temp = temp->right;
    }
    cout << "Account not found.\n";
}


void Node::showAllAccounts() {
    Node* temp = head;
    if (!temp) {
        cout << "No accounts available.\n";
        return;
    }

    while (temp) {
        printAccountDetails(temp);
        temp = temp->right;
    }
}

void Node::searchAccount(long long accNumber) {
    Node* temp = head;
    while (temp) {
        if (temp->accountNumber == accNumber) {
            printAccountDetails(temp);
            return;
        }
        temp = temp->right;
    }
    cout << "Account not found.\n";
}

void Node::deleteAccount(long long accNumber) {
    Node* temp = head;
    while (temp) {
        if (temp->accountNumber == accNumber) {
            if (temp->left) temp->left->right = temp->right;
            if (temp->right) temp->right->left = temp->left;
            if (temp == head) head = temp->right;

            delete temp;
            cout << "Account deleted successfully.\n";
            return;
        }
        temp = temp->right;
    }
    cout << "Account not found.\n";
}

void Node::editAccount(long long accNumber) {
    Node* temp = head;
    while (temp) {
        if (temp->accountNumber == accNumber) {
            cout << "\n********** Edit Account **********\n";
            cout << "1. Edit First Name\n";
            cout << "2. Edit Last Name\n";
            cout << "3. Edit Phone Number\n";
            cout << "4. Edit PIN\n";
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "Enter new First Name: ";
                    cin >> temp->firstName;
                    break;
                case 2:
                    cout << "Enter new Last Name: ";
                    cin >> temp->lastName;
                    break;
                case 3:
                    cout << "Enter new Phone Number: ";
                    cin >> temp->phoneNumber;
                    break;
                case 4:
                    cout << "Enter new PIN: ";
                    int newPin;
                    cin >> newPin;
                    while (newPin < 1000 || newPin > 9999) {
                        cout << "Invalid PIN! Enter a valid 4-digit PIN: ";
                        cin >> newPin;
                    }
                    temp->pin = newPin;
                    break;
                default:
                    cout << "Invalid choice.\n";
                    return;
            }
            cout << "Account updated successfully.\n";
            return;
        }
        temp = temp->right;
    }
    cout << "Account not found.\n";
}

void Node::customerMenu() {
    while (true) {
        cout << "\n********** Customer Menu **********\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Amount\n";
        cout << "3. Withdraw Amount\n";
        cout << "4. View Transaction History\n";
        cout << "5. Invest in Savings\n";
        cout << "6. Pay Bill\n";
        cout << "7. Back to Main Menu\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2: {
                long long accNumber;
                cout << "Enter your account number: ";
                cin >> accNumber;
                depositAmount(accNumber);
                break;
            }
            case 3: {
                long long accNumber;
                cout << "Enter your account number: ";
                cin >> accNumber;
                withdrawAmount(accNumber);
                break;
            }
            case 4: {
                long long accNumber;
                cout << "Enter your account number: ";
                cin >> accNumber;
                showTransactionHistory(accNumber);
                break;
            }
            case 5: {
                long long accNumber;
                cout << "Enter your account number: ";
                cin >> accNumber;
                investInSavings(accNumber);
                break;
            }
            case 6: {
                long long accNumber;
                cout << "Enter your account number: ";
                cin >> accNumber;
                payBill(accNumber);
                break;
            }
            case 7:
                return;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}

void Node::staffMenu() {
    while (true) {
        cout << "\n********** Staff Menu **********\n";
        cout << "1. View All Accounts\n";
        cout << "2. Search Account\n";
        cout << "3. Delete Account\n";
        cout << "4. Edit Account\n";
        cout << "5. Back to Main Menu\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                showAllAccounts();
                break;
            case 2: {
                long long accNumber;
                cout << "Enter account number: ";
                cin >> accNumber;
                searchAccount(accNumber);
                break;
            }
            case 3: {
                long long accNumber;
                cout << "Enter account number: ";
                cin >> accNumber;
                deleteAccount(accNumber);
                break;
            }
            case 4: {
                long long accNumber;
                cout << "Enter account number: ";
                cin >> accNumber;
                editAccount(accNumber);
                break;
            }
            case 5:
                return;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}

void Node::atmService(long long accNumber) {
    Node* temp = head;
    while (temp) {
        if (temp->accountNumber == accNumber) {
            cout << "\nEnter PIN: ";
            int inputPin;
            cin >> inputPin;
            if (temp->pin != inputPin) {
                cout << "Invalid PIN!\n";
                return;
            }

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
