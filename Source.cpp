#include <iostream>
#include <unordered_map>
#include <chrono>
#include <thread>
#include <conio.h>
#include <queue>
#include <stdexcept>
#include "DigitalWallet.h"

using namespace std;

DigitalWallet del;

string maskedInput() {
    const char BACKSPACE = 8;
    const char ENTER = 13;
    queue<char> passwordQueue;
    char ch;

    cout << "Enter password: ";
    while (true) {
        ch = _getch();
        if (ch == ENTER) {
            cout << endl;
            break;
        }
        else if (ch == BACKSPACE) {
            if (!passwordQueue.empty()) {
                passwordQueue.pop();
                cout << "\b \b";
            }
        }
        else {
            passwordQueue.push(ch);
            cout << '*';
        }
    }

    // Construct the password string from the queue
    string password;
    while (!passwordQueue.empty()) {
        password += passwordQueue.front();
        passwordQueue.pop();
    }
    return password;
}

void printMainMenu() {
    cout << "\n===== Digital Wallet Services =====" << endl;
    cout << "1. Deposit Fund\n";
    del.delay(500);
    cout << "2. Withdraw Funds\n";
    del.delay(500);
    cout << "3. View Balance\n";
    del.delay(500);
    cout << "4. Send Money\n";
    del.delay(500);
    cout << "5. Request Money\n";
    del.delay(500);
    cout << "6. View Transaction History\n";
    del.delay(500);
    cout << "7. Notification\n";
    del.delay(500);
    cout << "8. Edit your information\n";
    del.delay(500);
    cout << "9. Logout to main menu\n";
    del.delay(500);
    cout << "===============================" << endl;
    cout << "Enter your choice: ";
}

void mainMenuUser(DigitalWallet& mywallet, const string& userAddress) {
    int choice;
    bool exit = false;
    double amount;
    string recipient;

    while (!exit) {
        printMainMenu();
        try {
            cin >> choice;
            if (cin.fail()) {
                throw runtime_error("Invalid input type. Please enter a valid integer.");
            }

            switch (choice) {
                case 1: {
                    do {
                        cout << "\nPlease enter deposit amount: ";
                        cin >> amount;

                        if (cin.fail()) {
                            throw runtime_error("Invalid input type. Please enter a valid number.");
                        }
                        if (amount <= 0) {
                            cout << "Please enter a valid amount";
                            continue;
                        }
                        mywallet.deposit(userAddress, amount);
                        cout << "Deposit successful" << endl;
                        string tryAgain;
                        cout << "\nDo you want to make another deposit?\n Y=> Yes / other key => No: ";
                        cin >> tryAgain;
                        if (tryAgain != "Y" && tryAgain != "y") {
                            break;
                        }
                    } while (true);
                    break;
                }
                case 2: {
                    do {
                        cout << "\nEnter withdrawal amount: ";
                        cin >> amount;

                        if (cin.fail()) {
                            throw runtime_error("Invalid input type. Please enter a valid number.");
                        }
                        if (amount <= 0) {
                            cout << "Please enter a valid amount";
                            continue;
                        }                        if (mywallet.withdrawal(userAddress, amount)) {
                            cout << "Withdrawal successful!" << endl;
                        }
                        else {
                            cout << "Error: Insufficient balance or withdrawal failed." << endl;
                        }

                        string tryAgain;
                        cout << "\nDo you want to make another withdrawal?\n Y=> Yes / other key => No: ";
                        cin >> tryAgain;
                        if (tryAgain != "Y" && tryAgain != "y") {
                            break;
                        }
                    } while (true);
                    break;
                }
                case 3: {
                    mywallet.viewBalance(userAddress);
                    break;
                }
                case 4: {
                    do {
                        cout << "\nEnter recipient address: ";
                        cin >> recipient;
                        if (recipient == userAddress) {
                            cout << "You can't send money to yourself";
                            continue;
                        }
                        cout << "Enter amount to send: ";
                        cin >> amount;
                        if (cin.fail()) {
                            throw runtime_error("Invalid input type. Please enter a valid number.");
                        }
                        if (amount <= 0) {
                            cout << "Please enter a valid amount";
                            continue;
                        }

                        mywallet.Send(userAddress, recipient, amount);
                        cout << "Transaction sent successfully!" << endl;

                        string tryAgain;
                        cout << "\nDo you want to send money to another recipient?\n Y=> Yes / other key => No: ";
                        cin >> tryAgain;
                        if (tryAgain != "Y" && tryAgain != "y") {
                            break;
                        }
                    } while (true);
                    break;
                }
                case 5: {
                    do {
                        cout << "\nEnter recipient address: ";
                        cin >> recipient;
                        if (recipient == userAddress) {
                            cout << "You can't request money from yourself";
                            continue;
                        }
                        cout << "Enter amount money to request: ";
                        cin >> amount;
                        if (cin.fail()) {
                            throw runtime_error("Invalid input type. Please enter a valid number.");
                        }
                        if (amount <= 0) {
                            cout << "Please enter a valid amount";
                            continue;
                        }
                        mywallet.Req(userAddress, recipient, amount);

                        string tryAgain;
                        cout << "\nDo you want to make another request?\n Y=> Yes / other key => No: ";
                        cin >> tryAgain;
                        if (tryAgain != "Y" && tryAgain != "y") {
                            break;
                        }
                    } while (true);
                    break;
                }
                case 6: {
                    do {
                        mywallet.MyHistory(userAddress);

                        string tryAgain;
                        cout << "\nDo you want to view transaction history again?\n Y=> Yes / other key => No: ";
                        cin >> tryAgain;
                        if (tryAgain != "Y" && tryAgain != "y") {
                            break;
                        }
                    } while (true);
                    break;
                }
                case 7: {
                    mywallet.notification();
                    break;
                }
                case 8: {
                    do {
                        mywallet.editProfile(userAddress);

                        string tryAgain;
                        cout << "\nDo you want to edit profile again?\n Y=> Yes / other key => No: ";
                        cin >> tryAgain;
                        if (tryAgain != "Y" && tryAgain != "y") {
                            break;
                        }
                    } while (true);
                    break;
                }
                case 9: {
                    cout << "Logging you out..." << endl;
                    exit = true;
                    break;
                }
                default: {
                    cout << "Invalid choice. Please try again." << endl;
                    break;
                }
            }
        }
        catch (const exception& e) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cerr << "Error: " << e.what() << endl;
        }
    }
}

void AdminMenu(DigitalWallet& mywallet) {
    int choice;
    do {
        try {
            cout << "\n===== Admin Menu =====" << endl;
            del.delay(500);
            cout << "1. Edit User Profile" << endl;
            del.delay(500);
            cout << "2. View All Transactions" << endl;
            del.delay(500);
            cout << "3. Create New User" << endl;
            del.delay(500);
            cout << "4. Create New Admin" << endl;
            del.delay(500);
            cout << "5. Enable Account" << endl;
            del.delay(500);
            cout << "6. Disable Account" << endl;
            del.delay(500);
            cout << "7. Logout" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    do {
                        string address;
                        cout << "\nEnter user address to edit profile: ";
                        cin >> address;
                        mywallet.editProfile(address);

                        string tryAgain;
                        cout << "\nDo you want to edit another user profile?\n Y=> Yes / other key => No: ";
                        cin >> tryAgain;
                        if (tryAgain != "Y" && tryAgain != "y") {
                            break;
                        }
                    } while (true);
                    break;
                }
                case 2: {
                    do {
                        cout << "\n===== All Transactions =====" << endl;
                        for (const auto& transaction : mywallet.History) {
                            cout << "Transaction Type: " << transaction.Type << endl;
                            cout << "Sender Address: " << transaction.SAddress << endl;
                            cout << "Receiver Address: " << transaction.RAddress << endl;
                            cout << "Amount: $" << transaction.amount << endl;
                            cout << "============================" << endl;
                        }

                        string tryAgain;
                        cout << "\nDo you want to view transactions again?\n Y=> Yes / other key => No: ";
                        cin >> tryAgain;
                        if (tryAgain != "Y" && tryAgain != "y") {
                            break;
                        }
                    } while (true);
                    break;
                }
                case 3: {
                    do {
                        string address, name, phone, email, password;
                        cout << "\nEnter address: ";
                        cin >> address;
                        cout << "Enter name: ";
                        cin >> name;
                        cout << "Enter phone number: ";
                        cin >> phone;
                        cout << "Enter email: ";
                        cin >> email;
                        cout << "Enter password: ";
                        cin >> password;
                        mywallet.signUp(address, name, phone, email, password);

                        string tryAgain;
                        cout << "\nDo you want to create another user?\n Y=> Yes / other key => No: ";
                        cin >> tryAgain;
                        if (tryAgain != "Y" && tryAgain != "y") {
                            break;
                        }
                    } while (true);
                    break;
                }
                case 4: {
                    do {
                        string address, name, phone, email, password;
                        cout << "\nEnter address: ";
                        cin >> address;
                        cout << "Enter name: ";
                        cin >> name;
                        cout << "Enter phone number: ";
                        cin >> phone;
                        cout << "Enter email: ";
                        cin >> email;
                        cout << "Enter password: ";
                        cin >> password;
                        DigitalWallet::User newUser{ name, 0, password, email, phone, true };
                        mywallet.mapOfUsers[address] = newUser;
                        cout << "Done you create new admin!" << endl;

                        string tryAgain;
                        cout << "\nDo you want to create another admin?\n Y=> Yes / other key => No: ";
                        cin >> tryAgain;
                        if (tryAgain != "Y" && tryAgain != "y") {
                            break;
                        }
                    } while (true);
                    break;
                }
                case 5: {
                    do {
                        string address;
                        cout << "\nEnter user address to enable account: ";
                        cin >> address;
                        if (mywallet.mapOfUsers.find(address) != mywallet.mapOfUsers.end()) {
                            if (mywallet.mapOfUsers[address].isActive) {
                                cout << "Account already enabled" << endl;
                            }
                            else {
                                mywallet.mapOfUsers[address].isActive = true;
                                cout << "Account enabled successfully!" << endl;
                            }
                        }
                        else {
                            cout << "User not found. Please enter a valid user address." << endl;
                        }

                        string tryAgain;
                        cout << "\nDo you want to enable another account?\n Y=> Yes / other key => No: ";
                        cin >> tryAgain;
                        if (tryAgain != "Y" && tryAgain != "y") {
                            break;
                        }
                    } while (true);
                    break;
                }
                case 6: {
                    do {
                        string address;
                        cout << "\nEnter user address to disable account: ";
                        cin >> address;
                        if (mywallet.mapOfUsers.find(address) != mywallet.mapOfUsers.end()) {
                            mywallet.mapOfUsers[address].isActive = false;
                            cout << "Account disabled successfully!" << endl;
                        }
                        else {
                            cout << "User not found. Please enter a valid user address." << endl;
                        }

                        string tryAgain;
                        cout << "\nDo you want to disable another account?\n Y=> Yes / other key => No: ";
                        cin >> tryAgain;
                        if (tryAgain != "Y" && tryAgain != "y") {
                            break;
                        }
                    } while (true);
                    break;
                }
                case 7: {
                    cout << "Logging out..." << endl;
                    return;
                }
                default: {
                    cout << "Invalid choice. Please try again." << endl;
                    break;
                }
            }
        }
        catch (const exception& e) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cerr << "Error: " << e.what() << endl;
        }
    } while (true);
}


int main() {
    DigitalWallet mywallet;
    int choice;
    bool loggedIn = false;
    string userAddress;

    mywallet.init();
    do {
        cout << "\n======================================" << endl;
        cout << "===== Welcome to Digital Wallet =====" << endl;
        cout << "======================================" << endl;
        del.delay(1500);
        cout << "1. Sign Up" << endl;
        del.delay(500);
        cout << "2. Log In" << endl;
        del.delay(500);
        cout << "3. Exit" << endl;
        del.delay(500);
        cout << "Enter your choice:- ";

        try {
            cin >> choice;
            if (cin.fail()) {
                throw runtime_error("Invalid input type. Please enter a valid integer.");
            }

            switch (choice) {
                case 1: {
                    string address, name, phone, email, password;
                    cout << "\nEnter address: ";
                    cin >> address;
                    cout << "Enter name: ";
                    cin >> name;
                    cout << "Enter phone number: ";
                    cin >> phone;
                    cout << "Enter email: ";
                    cin >> email;
                    password = maskedInput();
                    mywallet.signUp(address, name, phone, email, password);

                    break;
                }
                case 2: {
                    string address, password;
                    cout << "\nEnter address: ";
                    cin >> address;
                    password = maskedInput();
                    loggedIn = mywallet.login(address, password);
                    if (loggedIn) {
                        //   userAddress = address;
                        cout << "Logged in successfully!" << endl;
                        if (mywallet.isadmin(address))
                        {
                            mainMenuUser(mywallet, address);
                        }
                        else {
                            AdminMenu(mywallet);
                        }
                    }
                    break;
                }
                case 3: {
                    cout << "Exiting..." << endl;
                    exit(0);
                }
                default: {
                    cout << "Invalid choice. Please try again." << endl;
                    break;
                }
            }
        }
        catch (const exception& e) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cerr << "Error: " << e.what() << endl;
        }
    } while (true);
}