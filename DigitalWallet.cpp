#include "DigitalWallet.h"
#include <iostream>
#include <unordered_map>
#include <regex>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

void DigitalWallet::delay(int milliseconds) {
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

void DigitalWallet::init() {
    mapOfUsers["admin"] = { "admin",0, Hash("admin"), "admin@email.com", "01200000000",true,true };
    mapOfUsers["a"] = { "a",100, Hash("a"), "a", "01200000000",false,true };
    mapOfUsers["b"] = { "b",150, Hash("b"), "b", "01200000000",false,true };

}
bool DigitalWallet::isadmin(string address) {
    if (!mapOfUsers[address].isAdmin) {
        return true;
    }
    return false;
}

void DigitalWallet::Send(string SA, string RA, double amount) {
    auto it = mapOfUsers.find(RA);
    if (it == mapOfUsers.end()) {
        cout << "there are no one with the same address\n";
    }
    else {
        mapOfUsers[SA].balance -= amount;
        mapOfUsers[RA].balance += amount;
        transactions.push_back({ SA, RA, amount, true, -1, "Send" });
        AddRec(transactions[TransactionCounter]);
        TransactionCounter++;
    }
}

void DigitalWallet::AddRec(Transaction tra) {
    if (tra.Accepted) {
        History.push_back(tra);
        cout << "Transaction is recorded!" << endl;
    }
}

void DigitalWallet::Req(string SA, string RA, double amount) {
    auto it = mapOfUsers.find(RA);
    if (it == mapOfUsers.end()) {
        cout << "there are no one with the same address\n";
    }
    else {
        transactions.push_back({ SA, RA, amount, true, -1, "Request" });
        AddRec(transactions[TransactionCounter]);
        RequestHistory.push_back(transactions[TransactionCounter]);
        TransactionCounter++;
        cout << "Request sent successfully!" << endl;
    }
}

void DigitalWallet::MyHistory(string Address) {
    if (TransactionCounter == 0) {
        cout << "There is no transaction on this account.\n";
        return;
    }
    for (int i = 0; i <= TransactionCounter; i++) {
        if (Address == transactions[i].SAddress) {
            cout << "Transaction " << i + 1 << ":" << endl;
            delay(500);
            cout << "Transaction Type : " << transactions[i].Type << endl;
            delay(500);
            cout << "Paid: " << transactions[i].amount << endl;
            delay(500);
            cout << "For: " << transactions[i].RAddress << endl;
            cout << "========================================\n";
            delay(1000);

        }
        else if (Address == transactions[i].RAddress) {
            cout << "Transaction " << i + 1 << ":" << endl;
            delay(500);
            cout << "Transaction Type : " << transactions[i].Type << endl;
            delay(500);
            cout << "Received: " << transactions[i].amount << endl;
            delay(500);
            cout << "From: " << transactions[i].SAddress << endl;
            delay(500);
            cout << "========================================\n";
            delay(1000);
        }
    }
}

void DigitalWallet::notification() {
    int choice;
    for (int i = 0; i < RequestHistory.size(); i++) {
        cout << "Request " << i + 1 << " from: " << RequestHistory[i].SAddress << endl;
        cout << "Requested amount:" << RequestHistory[i].amount << " $\n";
    }

    cout << "Enter the number of the request you want to respond to (0 to exit): ";
    cin >> choice;

    if (choice > 0 && choice <= RequestHistory.size()) {
        int response;
        cout << "To accept press 1, to reject press 0: ";
        cin >> response;

        if (response == 1) {

            if (mapOfUsers[RequestHistory[choice - 1].RAddress].balance > RequestHistory[choice - 1].amount) {
                cout << "The request is accepted." << endl;
                Send(RequestHistory[choice - 1].RAddress, RequestHistory[choice - 1].SAddress, RequestHistory[choice - 1].amount);
                RequestHistory.erase(RequestHistory.begin() + choice - 1);
            }
            else {
                cout << "The request is rejected, Insufficient balance " << endl;
            }
        }
        else {
            cout << "The request is rejected!" << endl;
            RequestHistory.erase(RequestHistory.begin() + choice - 1);

        }
    }


}


bool DigitalWallet::withdrawal(string address, double amount) {
    if (mapOfUsers[address].balance == 0) {
        cout << "Withdrawal is not allowed. Balance is zero." << endl;
        return false;
    }
    else if (mapOfUsers[address].balance < amount) {
        cout << "Insufficient balance for withdrawal." << endl;
        return false;
    }

    mapOfUsers[address].balance -= amount;
    transactions.push_back({ "System", address, amount, true, 1, "withdrawal" });
    AddRec(transactions[TransactionCounter]);
    TransactionCounter++;
    return true;

}
void DigitalWallet::deposit(string address, double amount) {
    mapOfUsers[address].balance += amount;
    transactions.push_back({ "System", address, amount, true, 1, "deposit" }); // Record the deposit transaction
    AddRec(transactions[TransactionCounter]);
    TransactionCounter++;
    return;
}


string DigitalWallet::Hash(const string& password) {

    string hash;
    for (char c : password) {
        hash += int(c) + 5 * 2;
    }
    return hash;
}


void DigitalWallet::signUp(string address, string name, string phone_number, string email, string password) {
    if (mapOfUsers.find(address) != mapOfUsers.end()) {
        cout << "User with this address already exists. Please choose a different address." << endl;
        return;
    }
    //    while (true) {
    //        if (password.length() < 8 ) {
    //            cout << "Password must be at least 8 characters, Please try again: ";
    //            cin >> password;
    //            continue;
    //        }
    //
    //        string specialCharsPass = "<>?':|}{;+=_-)(*&^%$#@!~./[]";
    //        bool   hasSpecialChar = false, hasUpperCase = false, hasLowerCase = false, hasNumber = false;
    //
    //        for (char isExist : password) {
    //            if (islower(isExist)) {//islower function check if char is in lowercase or not
    //                hasLowerCase = true;
    //            }
    //            else if (isupper(isExist)) {
    //                hasUpperCase = true;
    //            }
    //            else if (isdigit(isExist)) {
    //                hasNumber = true;
    //            }
    //            else if (specialCharsPass.find(isExist) != string::npos) {
    //                hasSpecialChar = true;
    //            }
    //        }
    //
    //        if (!hasUpperCase ||!hasLowerCase ||!hasNumber ||!hasSpecialChar) {
    //            cout << "Password must contain at least one lowercase letter, one uppercase letter, one digit, and one special character. Please try again: ";
    //            cin >> password;
    //            continue;
    //        }
    //        while (true) {
    //
    //            regex emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    //            if (!regex_match(email, emailRegex)) {
    //                cout << "Invalid email format. Please try again:";
    //                cin >> email;
    //                continue;
    //            }
    //           // cout << "Email is valid" << "\n";
    //
    //            break;
    //       }
    //
    //        while (true) {
    //
    //
    //            regex phoneRegex(R"(01\d{9})");
    //            if (!regex_match(phone_number, phoneRegex)) {
    //                cout << "Invalid phone number format. Please enter an 11-digit number starting with 01:";
    //                cin >> phone_number;
    //                continue;
    //            }
    //
    //          //  cout << "Phone number is valid" << "\n";
    //            break;
    //        }
    string hashedPassword = Hash(password);

    User newUser{ name, 0, hashedPassword, email, phone_number };
    mapOfUsers[address] = newUser;//newuser is value of hashtable and the key is address
    cout << "Sign up successful!" << endl;
    cout << "Please login now";
    // break;
// }
}


bool DigitalWallet::login(string address, string pass) {
    string hashedPassword;
    auto it = mapOfUsers.find(address);
    if (it == mapOfUsers.end()) {
        cout << "User not found. Please sign up first." << endl;
        return false;
    }

    if (!it->second.isActive) {
        cout << "Your account is currently disabled. Please contact the admin for assistance." << endl;
        return false;
    }

    hashedPassword = Hash(pass);
    if (hashedPassword == it->second.password) {
        cout << "Login successful. Welcome, " << it->second.name << "!" << endl;
        return true;
    }
    else {
        cout << "Incorrect password. Login failed." << endl;
        return false;
    }
}
void DigitalWallet::viewBalance(string address) {
    auto it = mapOfUsers.find(address);
    if (it == mapOfUsers.end()) {
        cout << "Invalid Address." << endl;
    }
    else {
        cout << "Your current balance: $" << it->second.balance << endl;
    }
}

void DigitalWallet::editProfile(string address)
{
    int choice;
    string response;
    string newname;
    string newpassword;
    string newemail;
    string newphonenumber;
    auto it = mapOfUsers.find(address);
    if (it == mapOfUsers.end()) {
        cout << "there are no one with the same address\n";
    }
    else {
        do {
            cout << "to edit press:\n";
            delay(500);
            cout << "1. For Name\n";
            delay(500);
            cout << "2. For Password\n";
            delay(500);
            cout << "3. For Email\n";
            delay(500);
            cout << "4. For Phone Number\n";
            delay(500);
            cout << "5. to back to main menu ";
            delay(500);
            cin >> choice;
            switch (choice) {
                case 1:
                    cout << "Enter new name: ";
                    cin >> newname;
                    mapOfUsers[address].name = newname;
                    cout << "Done! \n";
                    cout << "to edit another data press 1,any other key to back: ";
                    cin >> response;
                    break;

                case 2:
                    cout << "Enter new password: ";
                    cin >> newpassword;
                    mapOfUsers[address].password = Hash(newpassword);
                    cout << "Done! \n";
                    cout << "to edit another data press 1,any other key to back";
                    cin >> response;
                    break;

                case 3:
                    cout << "Enter new Email: ";
                    cin >> newemail;
                    mapOfUsers[address].email = newemail;
                    cout << "Done! \n";
                    cout << "to edit another data press 1,any other key to back";
                    cin >> response;
                    break;

                case 4:
                    cout << "Enter new phone number : ";
                    cin >> newphonenumber;
                    mapOfUsers[address].phone_number = newphonenumber;
                    cout << "Done! \n";
                    cout << "to edit another data press 1,any other key to back";
                    cin >> response;
                    break;
                case 5:
                    break;
                default:
                    cout << "please choose valid number";
                    response = "1";
                    continue;

            }


        } while (response == "1");
    }
    system("cls");
}