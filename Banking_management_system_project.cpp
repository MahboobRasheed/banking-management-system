#include <iostream>
#include <string>
#include <stack>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <iomanip>
#include <algorithm>

using namespace std;

bool menuChoice(string choice)
{
    for (int i = 0; i < choice.size(); ++i)
    {
        if (!isdigit(choice[i]))
        {
            return false;
        }
    }
    if (choice.empty())
    {
        return false;
    }
    for (int i = 0; i < choice.size(); ++i)
    {
        if (choice[i] == ' ')
        {
            return false;
        }
    }
    return true;
}

bool phoneValidation(string input)
{
    if (input.empty())
    {
        return false;
    }
    if (input[0] != '0')
    {
        return false;
    }

    if (input.size() > 1 && input[1] != '3')
    {
        return false;
    }

    for (int i = 0; i < input.size(); ++i)
    {
        if (!isdigit(input[i]) && input[i] == ' ')
        {
            return false;
        }
    }
    if (input.size() == 11)
    {
        return true;
    }
    return false;
}

bool pinValid(string token)
{
    if (token.empty())
    {
        return false;
    }
    for (int i = 0; i < token.size(); ++i)
    {
        if (!isdigit(token[i]) && token[i] == ' ')
        {
            return false;
        }
    }
    if (token.size() == 4)
    {
        return true;
    }
}

bool accValid(string token)
{
    if (token.empty())
    {
        return false;
    }
    for (int i = 0; i < token.size(); ++i)
    {
        if (!isdigit(token[i]) && token[i] == ' ')
        {
            return false;
        }
    }
    if (token.size() == 16)
    {
        return true;
    }
    return false;
}

bool nameValid(const string &name)
{
    if (name.empty()) // If name is empty, return false
    {
        return false;
    }

    for (char ch : name) // Loop through each character in the name
    {
        if (!isalpha(ch) && ch != ' ') // Check if character is not an alphabet and not a space
        {
            return false; // Invalid character found
        }
    }
    return true; // All characters are valid (either alphabet or space)
}

bool cnicValid(string token)
{
    if (token.empty())
    {
        return false;
    }
    for (int i = 0; i < token.size(); ++i)
    {
        if (!isdigit(token[i]) && token[i] == ' ')
        {
            return false;
        }
    }
    if (token.size() == 13)
    {
        return true;
    }
    return false;
}

class Node
{
private:
    string firstName, lastName, cnic, gender, phoneNumber;
    int age;
    int pin;
    long long accountNumber;
    float balance;
    stack<string> transactionHistory;
    Node *left;
    Node *right;

    static long long generateAccountNumber()
    {
        return (long long)(rand() % 9000000000000000 + 1000000000000000);
    }
    bool isAllDigits(const string &str)
    {
        for (char c : str)
        {
            if (!isdigit(c))
            {
                return false;
            }
        }
        return true;
    }
    Node(string firstName, string lastName, string cnic, int age, string gender, string phoneNumber, float balance, int pin)
        : firstName(firstName), lastName(lastName), cnic(cnic), age(age), gender(gender),
          phoneNumber(phoneNumber), balance(balance), pin(pin),
          accountNumber(generateAccountNumber()), left(nullptr), right(nullptr)
    {
        transactionHistory.push("Account created with balance: " + to_string(balance));
    }

public:
    static Node *head;
    static void createAccount();
    static void addAccount(Node *);
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
    static void printAccountDetails(Node *);
};

Node *Node::head = nullptr;

bool Node::validatePin(long long accNumber, int enteredPin)
{
    Node *temp = Node::head;
    while (temp)
    {
        if (temp->accountNumber == accNumber)
        {
            return temp->pin == enteredPin; // Check if the entered PIN matches the stored PIN
        }
        temp = temp->right;
    }
    return false; // Return false if account not found
}

void Node::createAccount()
{
    cout << "\n** Create Account **\n";

    string firstName, lastName, cnic, gender, phoneNumber, pinStr;
    int age, pin;
    float balance;

    // cout << "Enter First Name: ";
    // cin >> firstName;
    // cout << "Enter Last Name: ";
    // cin >> lastName;
    while (true)
    {
        cout << "Enter Your First name: ";
        getline(cin, firstName);
        if (nameValid(firstName))
        {
            break;
        }
        cout << "\n\tInvalid name.\n";
    }

    // Clear the input buffer to avoid issues with getline

    // Get and validate last name
    while (true)
    {
        cout << "Enter Your last name: ";
        getline(cin, lastName);
        if (nameValid(lastName))
        {
            break;
        }
        cout << "\n\tInvalid name.\n";
    }

    while (true)
    {
        cout << "Enter Valid CNIC No: ";
        getline(cin, cnic);
        if (cnicValid(cnic))
        {
            break;
        }
        cout << "\n\tInvalid CNIC No.\n";
    }

    while (true)
    {
        cout << "Enter Age (18 or older): ";
        string ages;
        getline(cin, ages);
        if (stoi(ages) >= 18)
        {
            age = stoi(ages);
            break;
        }
        cout << "\n\t\tAge must be 18 or older. Enter again: ";
    }

    while (true)
    {
        cout << "Enter Gender (Male/Female): ";
        getline(cin , gender);
        transform(gender.begin(), gender.end(), gender.begin(), ::tolower);
        if (gender == "male" || gender == "female")
        {
            break;
        }
        cout << "\n\t\tInvalid Gender. Enter again (Male/Female): ";
    }

    while (true)
    {
        cout << "Enter Cell Number in PK: ";
        getline(cin, phoneNumber);
        if (phoneValidation(phoneNumber))
        {
            break;
        }
        cout << "\n\tInvalid Phone no.\n";
    }
while (true) {
    cout << "Enter Initial Deposit (minimum 500): ";
    string balanceStr;
    getline(cin , balanceStr);
    
    balance = stof(balanceStr); // Convert string to float
    if (balance >= 500) {
        break;
    }
    cout << "\n\t\tInitial deposit must be at least 500. Enter again: ";
}

    while (true)
    {
        cout << "Set you four digit pin" << endl;
        getline(cin, pinStr);
        if (pinValid(pinStr))
        {
            pin = stoi(pinStr);
            break;
        }
        cout << "\n\tInvalid PIN.\n";
    }

    Node *newNode = new Node(firstName, lastName, cnic, age, gender, phoneNumber, balance, pin);
    addAccount(newNode);

    cout << "Account created successfully! Your account number is: " << newNode->accountNumber << "\n";
}

void Node::addAccount(Node *newNode)
{
    if (!head)
    {
        head = newNode;
    }
    else
    {
        Node *temp = head;
        while (temp->right)
        {
            temp = temp->right;
        }
        temp->right = newNode;
        newNode->left = temp;
    }
}

void Node::depositAmount(long long accNumber)
{
    Node *temp = head;
    while (temp)
    {
        if (temp->accountNumber == accNumber)
        {
            int amount;
            while (true) {
    cout << "Enter amount to deposit: ";
    string amountStr;
    getline(cin,amountStr);

    amount = stof(amountStr); // Convert string to float
    if (amount > 0) {
        break;
    }
    cout << "\n\t\tInvalid amount! Enter again: ";
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

void Node::withdrawAmount(long long accNumber)
{
    Node *temp = head;
    while (temp)
    {
        if (temp->accountNumber == accNumber)
        {
            int amount;
            while (true) {
    cout << "Enter amount to withdraw: ";
    string amountStr;
    getline(cin, amountStr);

    amount = stof(amountStr); // Convert string to float
    if (amount > 0 && amount <= temp->balance - 500) {
        break;
    }
    cout << "\n\t\tInvalid amount! Ensure a minimum balance of 500 remains.\n";
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

void Node::showTransactionHistory(long long accNumber)
{
    Node *temp = head;
    while (temp)
    {
        if (temp->accountNumber == accNumber)
        {
            if (temp->transactionHistory.empty())
            {
                cout << "No transactions available.\n";
                return;
            }
            cout << "\n** Transaction History **\n";
            stack<string> history = temp->transactionHistory;
            while (!history.empty())
            {
                cout << history.top() << endl;
                history.pop();
            }
            return;
        }
        temp = temp->right;
    }
    cout << "Account not found.\n";
}

void Node::investInSavings(long long accNumber)
{
    Node *temp = head;
    while (temp)
    {
        if (temp->accountNumber == accNumber)
        {
            float amount;
            while (true) {
    cout << "Enter amount to invest (minimum balance of 500 required): ";
    string amountStr;
    getline(cin, amountStr);

    amount = stof(amountStr); // Convert string to float
    if (amount > 0 && temp->balance - amount >= 500) {
        break;
    }
    cout << "\n\t\tInvalid amount. Ensure you have at least 500 remaining balance.\n";
}


            string plan;
            while (true)
            {
                cout << "1. 1 Month (2% profit)\n";
                cout << "2. 6 Months (8% profit)\n";
                cout << "3. 1 Year (15% profit)\n";

                cout << "\nEnter your choice of Investment Plan: ";
                // cin.ignore(); // Clear any previous input before getline
                getline(cin, plan);

                if (plan == "1" || plan == "2" || plan == "3")
                {
                    break;
                }
                cout << "\n\t\tInvalid plan. Enter a valid option (1, 2, or 3): ";
            }

            float profit = 0;
            if (plan == "1")
            {
                profit = amount * 0.02;
            }
            else if (plan == "2")
            {
                profit = amount * 0.08;
            }
            else if (plan == "3")
            {
                profit = amount * 0.15;
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

void Node::payBill(long long accNumber)
{
    Node *temp = Node::head;
    int choice;
    while (temp)
    {
        // Use a public method or accessor to access accountNumber
        if (temp->accountNumber == accNumber)
        {
            while (true) {
    cout << "Which type of bill would you like to pay?\n";
    cout << "1. Electricity\n";
    cout << "2. Water\n";
    
    string choiceStr;
    getline(cin , choiceStr);

    int choice = stoi(choiceStr); // Convert string to int
    if (choice == 1 || choice == 2) {
        break;
    }
    cout << "\n\t\tInvalid choice. Enter a valid option (1 or 2): ";
}

 int amount=0;
            string billId;
            cout << "Enter Bill ID: ";
            getline(cin ,billId);

            // Validate Bill ID length based on the bill type
            if (choice == 1)
            { // Electricity
                if (billId.length() != 14 || !temp->isAllDigits(billId))
                {
                    cout << "Invalid electricity bill ID. It must be 14 digits.\n";
                    return;
                }
            }
            else if (choice == 2)
            { // Water
                if (billId.length() != 10 || !temp->isAllDigits(billId))
                {
                    cout << "Invalid water bill ID. It must be 10 digits.\n";
                    return;
                }
            }
            else
            {
                cout << "Invalid bill type choice.\n";
                return;
            }

            // Ask for the bill amount
           while (true) {
    cout << "Enter Bill Amount: ";
    string amountStr;
    getline(cin , amountStr);

    amount = stof(amountStr); // Convert string to float
    if (amount > 0 && amount <= temp->balance - 500) {
        break;
    }
    cout << "\n\t\tInvalid amount! Ensure a minimum balance of 500 remains.\n";
}


            // Validate the PIN using the public method
            int attempts = 0;
            while (attempts < 3) {
    cout << "Enter PIN: ";
    string enteredPinStr;
    getline(cin, enteredPinStr);

    int enteredPin = stoi(enteredPinStr); // Convert string to int
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

if (attempts >= 3) {
    cout << "Maximum attempts reached. Exiting...\n";
}


            cout << "Too many incorrect PIN attempts. Going back...\n";
            return;
        }
        temp = temp->right;
    }
    cout << "Account not found.\n";
}

void Node::showAllAccounts()
{
    Node *temp = head;
    if (!temp)
    {
        cout << "No accounts available.\n";
        return;
    }

    while (temp)
    {
        printAccountDetails(temp);
        temp = temp->right;
    }
}

void Node::searchAccount(long long accNumber)
{
    Node *temp = head;
    while (temp)
    {
        if (temp->accountNumber == accNumber)
        {
            printAccountDetails(temp);
            return;
        }
        temp = temp->right;
    }
    cout << "Account not found.\n";
}

void Node::deleteAccount(long long accNumber)
{
    Node *temp = head;
    while (temp)
    {
        if (temp->accountNumber == accNumber)
        {
            if (temp->left)
                temp->left->right = temp->right;
            if (temp->right)
                temp->right->left = temp->left;
            if (temp == head)
                head = temp->right;

            delete temp;
            cout << "Account deleted successfully.\n";
            return;
        }
        temp = temp->right;
    }
    cout << "Account not found.\n";
}
void Node::editAccount(long long accNumber)
{
    Node *temp = head;
    while (temp)
    {
        if (temp->accountNumber == accNumber)
        {
            cout << "\n** Edit Account **\n";
            cout << "1. Edit First Name\n";
            cout << "2. Edit Last Name\n";
            cout << "3. Edit Phone Number\n";
            cout << "4. Edit PIN\n";
            cout << "5. Back\n";
            cout << "Enter your choice: ";
            string choice;
            while (true)
            {
                cout << "\nEnter your choice: ";
                getline(cin, choice);
                if (menuChoice(choice)) // Assuming menuChoice is your validation function
                {
                    break;
                }
                cout << "\n\t\tInvalid input.\n";
            }

            if (choice == "1")
            {
                cout << "Enter new First Name: ";
                getline(cin, temp->firstName); // Use getline to capture the entire first name
            }
            else if (choice == "2")
            {
                cout << "Enter new Last Name: ";
                getline(cin, temp->lastName); // Use getline to capture the entire last name
            }
            else if (choice == "3")
            {
                while (true)
                {
                    cout << "Enter Cell Number in PK: ";
                    getline(cin, temp->phoneNumber);
                    if (phoneValidation(temp->phoneNumber))
                    {
                        break;
                    }
                    cout << "\n\tInvalid Phone no.\n";
                } // Assuming phone number is a string
            }
            else if (choice == "4")
            {
                int newPin;
                string pin;
                while (true)
                {
                    cout << "Enter new PIN: ";
                    getline(cin, pin); // Use getline to capture the PIN as a string first
                    if (pinValid(pin)) // Assuming pinValid checks PIN validity
                    {
                        newPin = stoi(pin); // Convert PIN to integer
                        break;
                    }
                    cout << "\n\tInvalid PIN.\n";
                }
                temp->pin = newPin;
            }
            else if (choice == "5")
            {
                cout << "Back to menu.\n";
                break;
            }
            else
            {
                cout << "Invalid choice.\n";
            }

            cout << "Account updated successfully.\n"; // Print success message after update
            return;                                    // Exit after updating the account
        }
        temp = temp->right; // Move to the next account in the list
    }
    cout << "Account not found.\n"; // If account not found
}

void Node::customerMenu()
{
    while (true)
    {
        cout << "\n** Customer Menu **\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Amount\n";
        cout << "3. Withdraw Amount\n";
        cout << "4. View Transaction History\n";
        cout << "5. Invest in Savings\n";
        cout << "6. Pay Bill\n";
        cout << "7. Back to Main Menu\n";
        string choice;
        while (true)
        {
            cout << "\nEnter your choice: ";
            getline(cin, choice);
            if (menuChoice(choice))
            {
                break;
            }
            cout << "\n\t\tInvalid input.\n";
        }

        if (choice == "1")
        {
            createAccount();
        }
        else if (choice == "2")
        {

            long long accNumber;
            string input;
            while (true)
            {
                cout << "Enter your account number: ";
                getline(cin, input);
                if (accValid(input))
                {
                    accNumber = stoll(input);
                    break;
                }
                cout << "\n\tInvalid Account No.\n";
            }
            depositAmount(accNumber);
        }
        else if (choice == "3")
        {
            long long accNumber;
            string input;
            while (true)
            {
                cout << "Enter your account number: ";
                getline(cin, input);
                if (accValid(input))
                {
                    accNumber = stoll(input);
                    break;
                }
                cout << "\n\tInvalid Account No.\n";
            }
            withdrawAmount(accNumber);
            break;
        }
        else if (choice == "4")
        {
            long long accNumber;
            string input;
            while (true)
            {
                cout << "Enter your account number: ";
                getline(cin, input);
                if (accValid(input))
                {
                    accNumber = stoll(input);
                    break;
                }
                cout << "\n\tInvalid Account No.\n";
            }
            showTransactionHistory(accNumber);
            break;
        }
        else if (choice == "5")
        {
            long long accNumber;
            string input;
            while (true)
            {
                cout << "Enter your account number: ";
                getline(cin, input);
                if (accValid(input))
                {
                    accNumber = stoll(input);
                    break;
                }
                cout << "\n\tInvalid Account No.\n";
            }
            investInSavings(accNumber);
            break;
        }
        else if (choice == "6")
        {
            long long accNumber;
            string input;
            while (true)
            {
                cout << "Enter your account number: ";
                getline(cin, input);
                if (accValid(input))
                {
                    accNumber = stoll(input);
                    break;
                }
                cout << "\n\tInvalid Account No.\n";
            }
            payBill(accNumber);
            break;
        }
        else if (choice == "7")
        {
            cout << "back to menu" << endl;
        }
        else
        {

            cout << "Invalid choice! Please try again.\n";
        }
    }
}

void Node::staffMenu()
{
    while (true)
    {
        cout << "\n** Staff Menu **\n";
        cout << "1. View All Accounts\n";
        // cout << "2. Search Account\n";
        cout << "2. Delete Account\n";
        cout << "3. Edit Account\n";
        cout << "4. Back to Main Menu\n";
        cout << "Enter choice: ";
        string choice;
        while (true)
        {
            cout << "\nEnter your choice: ";
            getline(cin, choice);
            if (menuChoice(choice))
            {
                break;
            }
            cout << "\n\t\tInvalid input.\n";
        }

        if (choice == "1")
        {
            showAllAccounts();
        }
        // else if (choice == "2")
        // {

        //     // long long accNumber;
        //     // string input;
        //     // while (true)
        //     // {
        //     //     cout << "Enter your account number: ";
        //     //     getline(cin, input);
        //     //     if (accValid(input))
        //     //     {
        //     //         accNumber = stoll(input);
        //     //         break;
        //     //     }
        //     //     cout << "\n\tInvalid Account No.\n";
        //     // }
        //     // searchAccount(accNumber);
        // }
        else if (choice == "2")
        {
            long long accNumber;
            string input;
            while (true)
            {
                cout << "Enter your account number: ";
                getline(cin, input);
                if (accValid(input))
                {
                    accNumber = stoll(input);
                    break;
                }
                cout << "\n\tInvalid Account No.\n";
            }
            deleteAccount(accNumber);
        }
        else if (choice == "3")
        {

            long long accNumber;
            string input;
            while (true)
            {
                cout << "Enter your account number: ";
                getline(cin, input);
                if (accValid(input))
                {
                    accNumber = stoll(input);
                    break;
                }
                cout << "\n\tInvalid Account No.\n";
            }
            editAccount(accNumber);
        }
        else if (choice == "4")
        {
            cout << "back to menu..." << endl;
            break;
        }
        else
        {

            cout << "Invalid choice! Please try again.\n";
        }
    }
}

void Node::atmService(long long accNumber)
{
    Node *temp = head;
    while (temp)
    {
        if (temp->accountNumber == accNumber)
        {
            int inputPin;
            string pin;
            while (true)
            {
                cout << "\nEnter PIN: ";
                if (pinValid(pin))
                {
                    inputPin = stoi(pin);
                    break;
                }
                cout << "\n\tInvalid PIN.\n";
            }
            if (temp->pin != inputPin)
            {
                cout << "Invalid PIN!\n";
                return;
            }

            while (true)
            {
                cout << "\n** ATM Service **\n";
                cout << "1. Transaction Slip\n";
                cout << "2. Withdraw Amount\n";
                cout << "3. Check Balance\n";
                cout << "4. Exit\n";
                string choice;
                while (true)
                {
                    cout << "\nEnter your choice: ";
                    getline(cin, choice);
                    if (menuChoice(choice))
                    {
                        break;
                    }
                    cout << "\n\t\tInvalid input.\n";
                }

                if (choice == "1")
                {

                    showTransactionHistory(accNumber);
                }

                else if (choice == "2")
                {
                    withdrawAmount(accNumber);
                }
                else if (choice == "3")
                {
                    cout << "Current Balance: " << fixed << setprecision(2) << temp->balance << "\n";
                }
                else if (choice == "4")
                {
                    cout << "Thank you for using ATM services!\n";
                    break;
                }
                else
                {
                    cout << "Invalid choice! Please try again.\n";
                }
            }
        }
        temp = temp->right;
    }
    cout << "Account not found.\n";
}

void Node::printAccountDetails(Node *account)
{
    cout << "\n** Account Details **\n";
    cout << "Account Number: " << account->accountNumber << "\n";
    cout << "Name: " << account->firstName << " " << account->lastName << "\n";
    cout << "CNIC: " << account->cnic << "\n";
    cout << "Age: " << account->age << "\n";
    cout << "Gender: " << account->gender << "\n";
    cout << "Phone Number: +92 " << account->phoneNumber << "\n";
    cout << "Balance: " << fixed << setprecision(2) << account->balance << "\n";
    cout << "*\n";
}
void nameApp()
{
    system("cls");
    cout << "\n\t||||||      / \\     ||\\\\    || ||  //  ||||||  ||\\\\    ||  ||||||||      ||||||||  \\\\    //  |||||||| |||||||||| |||||||| ||\\\\    //|| ";
    Sleep(120);
    cout << "\n\t||  //     // \\\\    || \\\\   || || //     ||    || \\\\   ||  ||            ||         \\\\  //   ||           ||     ||       || \\\\  // || ";
    Sleep(120);
    cout << "\n\t|||||     //   \\\\   ||  \\\\  || ||//\\     ||    ||  \\\\  ||  ||  ||||      ||||||||    \\\\//    ||||||||     ||     |||||||| ||  \\\\//  || ";
    Sleep(120);
    cout << "\n\t||  \\\\   //|||||\\\\  ||   \\\\ || ||/ \\\\    ||    ||   \\\\ ||  ||    ||            ||     //           ||     ||     ||       ||        ||";
    Sleep(120);
    cout << "\n\t||||||  //       \\\\ ||    \\\\|| ||   \\\\ ||||||  ||    \\\\||  ||||||||      ||||||||    //      ||||||||     ||     |||||||| ||        || \n\n";
    Sleep(120);
}
int main()
{
    nameApp();

    srand(time(0));

    while (true)
    {
        string choice;
        cout << "\n** Main Menu **\n";
        cout << "1. Customer Menu\n";
        cout << "2. ATM Service\n";
        cout << "3. Staff Menu\n";
        cout << "4. Exit\n";

        //cin.ignore();
        while (true)
        {
            cout << "\nEnter your choice: ";
            getline(cin, choice);
            if (menuChoice(choice))
            {
                break;
            }
            cout << "\n\t\tInvalid input.\n";
        }

        if (choice == "1")
        {
            Node::customerMenu();
        }
        else if (choice == "2")
        {
            long long accNumber;
            string input;
            while (true)
            {
                cout << "Enter your account number: ";
                getline(cin, input);
                if (accValid(input))
                {
                    accNumber = stoll(input);
                    break;
                }
                cout << "\n\tInvalid Account No.\n";
            }
            Node::atmService(accNumber);
        }
        else if (choice == "3")
        {
            Node::staffMenu();
        }
        else if (choice == "4")
        {
            cout << "Thank you for using our banking system!\n";
            break;
        }
        else
        {

            cout << "Invalid choice! Please try again.\n";
        }
    }
 return 0;
}
