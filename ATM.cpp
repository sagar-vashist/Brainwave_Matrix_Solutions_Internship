#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

class ATM {
private:
    string userPIN;
    double balance;
    vector<string> transactions;

    void printReceipt(const string& type, double amount) {
        cout << "\n----------- Receipt -----------\n";
        cout << "Transaction Type : " << type << endl;
        cout << "Amount           : ₹" << fixed << setprecision(2) << amount << endl;
        cout << "Available Balance: ₹" << balance << endl;
        cout << "-------------------------------\n";

        // Save to file
        ofstream receiptFile("receipt.txt");
        if (receiptFile.is_open()) {
            receiptFile << "----------- Receipt -----------\n";
            receiptFile << "Transaction Type : " << type << endl;
            receiptFile << "Amount           : ₹" << fixed << setprecision(2) << amount << endl;
            receiptFile << "Available Balance: ₹" << balance << endl;
            receiptFile << "-------------------------------\n";
            receiptFile.close();
            cout << "Receipt saved to 'receipt.txt'\n";
        } else {
            cout << "Failed to save receipt.\n";
        }
    }

public:
    ATM(string pin, double initialBalance) {
        userPIN = pin;
        balance = initialBalance;
    }

    bool authenticate(string pin) {
        return pin == userPIN;
    }

    void showMenu() {
        cout << "\n--- ATM Main Menu ---\n";
        cout << "1. Check Balance\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Mini Statement\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
    }

    void checkBalance() {
        cout << fixed << setprecision(2);
        cout << "Current Balance: ₹" << balance << endl;
        transactions.push_back("Checked Balance");
    }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid deposit amount.\n";
            return;
        }
        balance += amount;
        cout << "Deposited: ₹" << amount << endl;
        transactions.push_back("Deposited ₹" + to_string(amount));
        printReceipt("Deposit", amount);
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount.\n";
        } else if (amount > balance) {
            cout << "Insufficient balance.\n";
        } else {
            balance -= amount;
            cout << "Withdrawn: ₹" << amount << endl;
            transactions.push_back("Withdrawn ₹" + to_string(amount));
            printReceipt("Withdrawal", amount);
        }
    }

    void miniStatement() {
        cout << "\n--- Mini Statement ---\n";
        int count = 0;
        for (int i = transactions.size() - 1; i >= 0 && count < 5; --i, ++count) {
            cout << transactions[i] << endl;
        }
    }
};

int main() {
    ATM myATM("1234", 10000.0); // Let starting balance is ₹10,000
    string inputPIN;
    int attempts = 0;

    cout << "Welcome to the ATM Machine\n";

    do {
        cout << "Enter your 4-digit PIN: ";
        cin >> inputPIN;

        if (myATM.authenticate(inputPIN))
            break;

        cout << "Incorrect PIN. Try again.\n";
        attempts++;

    } while (attempts < 3);

    if (attempts == 3) {
        cout << "Too many failed attempts. Exiting.\n";
        return 1;
    }

    int choice;
    do {
        myATM.showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                myATM.checkBalance();
                break;
            case 2: {
                double amount;
                cout << "Enter amount to deposit (in ₹): ";
                cin >> amount;
                myATM.deposit(amount);
                break;
            }
            case 3: {
                double amount;
                cout << "Enter amount to withdraw (in ₹): ";
                cin >> amount;
                myATM.withdraw(amount);
                break;
            }
            case 4:
                myATM.miniStatement();
                break;
            case 5:
                cout << "Thank you for using the ATM.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}

