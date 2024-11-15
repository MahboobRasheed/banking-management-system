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
