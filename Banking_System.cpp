#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Account class with PIN
class Account {
public:
    int accountNumber;
    string name;
    double balance;
    int pin; // Added PIN

    Account(int accNo, string accName, double initialBalance, int pinCode) {
        accountNumber = accNo;
        name = accName;
        balance = initialBalance;
        pin = pinCode;
    }

    void display() {
        cout << "Account Number: " << accountNumber << ", Name: " << name << ", Balance: Rs" << balance << endl;
    }

    // Verify entered PIN
    bool verifyPin(int enteredPin) {
        return pin == enteredPin;
    }
};

vector<Account> accounts;

Account* findAccount(int accNo) {
    for (auto& acc : accounts) {
        if (acc.accountNumber == accNo) {
            return &acc;
        }
    }
    return nullptr;
}

// Create new account with PIN
void createAccount() {
    int accNo, pinCode;
    string name;
    double initialBalance;

    cout << "Enter Account Number: ";
    cin >> accNo;
    if (findAccount(accNo)) {
        cout << "Account already exists!\n";
        return;
    }

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Initial Balance: Rs";
    cin >> initialBalance;

    cout << "Set a 4-digit PIN: ";
    cin >> pinCode;

    if (pinCode < 1000 || pinCode > 9999) {
        cout << "Invalid PIN. Must be 4 digits.\n";
        return;
    }

    accounts.push_back(Account(accNo, name, initialBalance, pinCode));
    cout << "Account created successfully!\n";
}

// Secure deposit
void deposit() {
    int accNo, enteredPin;
    double amount;

    cout << "Enter Account Number: ";
    cin >> accNo;
    Account* acc = findAccount(accNo);
    if (!acc) {
        cout << "Account not found!\n";
        return;
    }

    cout << "Enter 4-digit PIN: ";
    cin >> enteredPin;
    if (!acc->verifyPin(enteredPin)) {
        cout << "Incorrect PIN!\n";
        return;
    }

    cout << "Enter Amount to Deposit: Rs";
    cin >> amount;
    if (amount <= 0) {
        cout << "Invalid amount!\n";
        return;
    }

    acc->balance += amount;
    cout << "Deposit successful! New Balance: Rs" << acc->balance << endl;
}

// Secure withdraw
void withdraw() {
    int accNo, enteredPin;
    double amount;

    cout << "Enter Account Number: ";
    cin >> accNo;
    Account* acc = findAccount(accNo);
    if (!acc) {
        cout << "Account not found!\n";
        return;
    }

    cout << "Enter 4-digit PIN: ";
    cin >> enteredPin;
    if (!acc->verifyPin(enteredPin)) {
        cout << "Incorrect PIN!\n";
        return;
    }

    cout << "Enter Amount to Withdraw: Rs";
    cin >> amount;
    if (amount > acc->balance || amount <= 0) {
        cout << "Invalid amount or insufficient funds!\n";
        return;
    }

    acc->balance -= amount;
    cout << "Withdrawal successful! New Balance: Rs" << acc->balance << endl;
}

// Secure transfer
void transfer() {
    int fromAccNo, toAccNo, enteredPin;
    double amount;

    cout << "Enter Sender Account Number: ";
    cin >> fromAccNo;
    Account* fromAcc = findAccount(fromAccNo);
    if (!fromAcc) {
        cout << "Sender account not found!\n";
        return;
    }

    cout << "Enter 4-digit PIN: ";
    cin >> enteredPin;
    if (!fromAcc->verifyPin(enteredPin)) {
        cout << "Incorrect PIN!\n";
        return;
    }

    cout << "Enter Receiver Account Number: ";
    cin >> toAccNo;
    Account* toAcc = findAccount(toAccNo);
    if (!toAcc) {
        cout << "Receiver account not found!\n";
        return;
    }

    cout << "Enter Amount to Transfer: Rs";
    cin >> amount;
    if (amount <= 0 || amount > fromAcc->balance) {
        cout << "Invalid amount or insufficient funds!\n";
        return;
    }

    fromAcc->balance -= amount;
    toAcc->balance += amount;
    cout << "Transfer successful!\n";
}

// View all accounts (no PIN required)
void viewAccounts() {
    if (accounts.empty()) {
        cout << "No accounts to show.\n";
        return;
    }
    for (auto& acc : accounts) {
        acc.display();
    }
}

// Main menu
int main() {
    int choice;

    do {
        cout << "\n=== Secure Online Banking System ===\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Transfer Money\n";
        cout << "5. View All Accounts\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: transfer(); break;
            case 5: viewAccounts(); break;
            case 6: cout << "Thank you for using the banking system!\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 6);

    return 0;
}