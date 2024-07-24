#include <QInputDialog>
#include <QRegularExpression>
#include <QMessageBox>
#include <QString>
#include "DigitalWallet.h"
#include "Files.h"
#include <vector>

using namespace std;


std::unordered_map<QString, DigitalWallet::User> mapOfUsers;
std::vector<DigitalWallet::Transaction> RequestHistory;
std::vector<DigitalWallet::Transaction> transactions;


int noticnt;


int DigitalWallet::getnotcnt(){
    return noticnt;
}

void DigitalWallet::setnotcnt(int x){
    noticnt = x;
    qDebug()<<x;
}
vector<DigitalWallet::Transaction> DigitalWallet::gettrans(){
    return transactions;
}

unordered_map<QString, DigitalWallet::User> DigitalWallet::getusers(){
    return mapOfUsers;
}

vector<DigitalWallet::Transaction> DigitalWallet::gethistory(){
    return RequestHistory;
}
void DigitalWallet::EditHis(int id){
    for (int i = 0; i < RequestHistory.size(); ++i) {
        if(RequestHistory[i].id==id){
            RequestHistory[i].PendigStatus = 1;
        }
    }

}
bool DigitalWallet::Edit(QString address, QString name, QString phone_number, QString email, QString password){

    // Hash the password for storage
    QString hashedPassword = Hash(password);

        User newUser{ name, 0, hashedPassword, email, phone_number,0 };
        mapOfUsers[address] = newUser;  // The key is the user's address


    // Inform the user about successful sign-up
    qDebug() << "Sign up successful!";
    qDebug() << "Please login now";

    return true;
}

void DigitalWallet::init() {
    Files files;
    files.Read(mapOfUsers, transactions, RequestHistory);
    noticnt = RequestHistory[RequestHistory.size()-1].id;
}

void DigitalWallet::fin() {
    Files files;
    files.Save(mapOfUsers, transactions, RequestHistory);
}

void DigitalWallet::Send(QString SA, QString RA, double amount) {
    auto senderIt = mapOfUsers.find(SA);
    auto receiverIt = mapOfUsers.find(RA);

    if (senderIt == mapOfUsers.end()) {
        qDebug() << "Error: Sender not found.";
        return;
    }

    if (receiverIt == mapOfUsers.end()) {
        qDebug() << "Error: Receiver not found.";
        QMessageBox::warning(nullptr, "Error", "Receiver not found.");

        return;
    }

    if(senderIt->second.balance < amount){
    QMessageBox::warning(nullptr, "Failed Transaction", "Insufficent balance. Please try again.");
        return;
    }
    senderIt->second.balance -= amount;
    receiverIt->second.balance += amount;
    transactions.push_back({ SA, RA, amount, true, -1, "Send" });

    QMessageBox::information(nullptr, "Transaction Successful", "Transaction successful.");
    Files files;
    files.Save(mapOfUsers, transactions, RequestHistory);

}

void DigitalWallet::MyHistory(QString Address) {
    if (transactions.empty()) {
        qDebug() << "There isn't any transactions yet.";
        return;
    }

    for (int i = 0; i < transactions.size(); i++) {
        if (Address == transactions[i].SAddress) {
            qDebug() << "Transaction " << i + 1 << ":";
            qDebug() << "Transaction Type: " << transactions[i].Type;
            qDebug() << "Paid: " << transactions[i].amount;
            qDebug() << "To: " << transactions[i].RAddress;
            qDebug() << "========================================";
        }
        else if (Address == transactions[i].RAddress) {
            qDebug() << "Transaction " << i + 1 << ":";
            qDebug() << "Transaction Type: " << transactions[i].Type;
            qDebug() << "Received: " << transactions[i].amount;
            qDebug() << "From: " << transactions[i].SAddress;
            qDebug() << "========================================";
        }
    }
}

void DigitalWallet::notification(QString Address) {
    QVector<int> requestIndices;
    for (int i = 0; i < RequestHistory.size(); i++) {
        if (RequestHistory[i].RAddress == Address) {
            qDebug() << "Request " << i + 1 << " from: " << RequestHistory[i].SAddress;
            qDebug() << "Requested amount:" << RequestHistory[i].amount << " $";
            requestIndices.push_back(i);
        }
    }

    if (requestIndices.isEmpty()) {
        qDebug() << "No pending requests.";
        return;
    }

    bool ok;
    int choice = QInputDialog::getInt(nullptr, "Respond to Request", "Enter the number of the request you want to respond to (0 to exit):", 0, 0, requestIndices.size(), 1, &ok);

    if (ok && choice > 0) {
        int index = requestIndices[choice - 1];
        int response = QInputDialog::getInt(nullptr, "Accept or Reject", "To accept press 1, to reject press 0:", 0, 0, 1, 1, &ok);

        if (ok) {
            if (response == 1) {
                if (mapOfUsers[RequestHistory[index].RAddress].balance > RequestHistory[index].amount) {
                    qDebug() << "The request is accepted.";
                    Send(RequestHistory[index].RAddress, RequestHistory[index].SAddress, RequestHistory[index].amount);
                    RequestHistory.erase(RequestHistory.begin() + index);
                } else {
                    qDebug() << "The request is rejected due to insufficient balance.";
                }
            } else {
                qDebug() << "The request is rejected.";
                RequestHistory.erase(RequestHistory.begin() + index);
            }
        }
    }
}

void DigitalWallet::Req(QString SA, QString RA, double amount) {
    auto it = mapOfUsers.find(RA);
    if (it == mapOfUsers.end()) {
        QMessageBox::warning(nullptr, "Error", "There are no one with the same address.");
    }
    else if (RA == SA){
        QMessageBox::warning(nullptr, "Error", "Cannot Request to yourself.");

    }
    else {
        transactions.push_back({ SA, RA, amount, true, -1, "Request"});

        RequestHistory.push_back({ SA, RA, amount, true, -1, "Request", ++noticnt});

        QMessageBox::information(nullptr, "Success", "Request sent successfully!");
    }
}

bool DigitalWallet::withdrawal(QString address, double amount) {
    if (mapOfUsers[address].balance == 0) {
        qDebug() << "Withdrawal is not allowed. Balance is zero.";
        QMessageBox::warning(nullptr, "Withdrawal failed", "Balance is zero.");

        return false;
    } else if (mapOfUsers[address].balance < amount) {
        qDebug() << "Insufficient balance for withdrawal.";
        QMessageBox::warning(nullptr, "Withdrawal failed", "Insufficient balance for withdrawal.");

        return false;
    }

    mapOfUsers[address].balance -= amount;

    Transaction withdrawal = { "System", address, amount, true, 1, "withdrawal" };
    transactions.push_back(withdrawal);
    QMessageBox::information(nullptr, "Withdrawal successful", "Your Withdrawal was successful.");

    qDebug() << "Withdrawal successful.";
    return true;
}

QString DigitalWallet::Hash(const QString& password) {
    QString hash;
    for (const QChar& c : password) {
        hash.append(QChar(c.unicode() + 5 * 2));
    }
    return hash;
}

bool DigitalWallet::signUp(QString address, QString name, QString phone_number, QString email, QString password,bool admin) {
    // Check if the user already exists

    if (mapOfUsers.find(address) != mapOfUsers.end()) {

        QMessageBox::warning(nullptr, "Address Conflict", "User with this address already exists. Please choose a different address.");
        qDebug() << "User with this address already exists. Please choose a different address.";
        return false;
    }
    bool isPasswordValid = true;
    bool isEmailValid = true;
    bool isPhoneNumberValid = true;

    // Validate password requirements
    if (password.length() < 8) {
        isPasswordValid = false;
        QMessageBox::warning(nullptr, "Password Requirement", "Password must be at least 8 characters. Please enter a valid password:");
    }

    // Check for password complexity requirements
    QString specialCharsPass = "<>?':|}{;+=_-)(*&^%$#@!~./[]";
    bool hasSpecialChar = false, hasUpperCase = false, hasLowerCase = false, hasNumber = false;

    for (QChar isExist : password) {
        if (isExist.isLower()) {
            hasLowerCase = true;
        } else if (isExist.isUpper()) {
            hasUpperCase = true;
        } else if (isExist.isDigit()) {
            hasNumber = true;
        } else if (specialCharsPass.contains(isExist)) {
            hasSpecialChar = true;
        }
    }

    if (!hasUpperCase || !hasLowerCase || !hasNumber || !hasSpecialChar) {
        isPasswordValid = false;
        QMessageBox::warning(nullptr, "Password Requirement", "Password must contain at least one lowercase letter, one uppercase letter, one digit, and one special character. Please enter a valid password:");
    }

    // Validate email format using regular expression
    QRegularExpression emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    if (!emailRegex.match(email).hasMatch()) {
        isEmailValid = false;
        QMessageBox::warning(nullptr, "Email Validation", "Invalid email format. Please enter a valid email:");
    }

    // Validate phone number format using regular expression
    QRegularExpression phoneRegex(R"(01\d{9})");
    if (!phoneRegex.match(phone_number).hasMatch()) {
        isPhoneNumberValid = false;
        QMessageBox::warning(nullptr, "Phone Number Validation", "Invalid phone number format. Please enter an 11-digit number starting with 01:");
    }

    // Check if any validation failed
    if (!isPasswordValid || !isEmailValid || !isPhoneNumberValid) {
        return false;
    }




    // Hash the password for storage
    QString hashedPassword = Hash(password);

    // Create a new user and add to the map
    if(admin==0){
        User newUser{ name, 0, hashedPassword, email, phone_number,0 };
        mapOfUsers[address] = newUser;  // The key is the user's address
    }
    else{
        User newUser{ name, 0, hashedPassword, email, phone_number,1 };
        mapOfUsers[address] = newUser;  // The key is the user's address
    }

    // Inform the user about successful sign-up
    qDebug() << "Sign up successful!";
    qDebug() << "Please login now";

    return true;
}

int DigitalWallet::login(QString &CurrentUser, QString address, QString pass) {

    QString hashedPassword;
    auto it = mapOfUsers.find(address);
    if (it == mapOfUsers.end()) {
        QMessageBox::information(nullptr, "Login Error", "User not found. Please sign up first.");
        return 0;
    }

    if (!(it->second).isActive) {
        QMessageBox::information(nullptr, "Login Error", "Your account is currently disabled. Please contact the admin for assistance.");
        return 0;
    }

    hashedPassword = Hash(pass);
    if (hashedPassword == (it->second).password) {

        QMessageBox::information(nullptr, "Login Successful", "Login successful. Welcome, " + (it->second).name + "!");

        if((it->second).isAdmin)
        {
            return 2;
        }
        CurrentUser = address;
          return 1;
    }
    else {
        QMessageBox::critical(nullptr, "Login Failed", "Incorrect password. Login failed.");
        return 0;
    }
}

void DigitalWallet::deposit(QString address, double amount){
    mapOfUsers[address].balance+=amount;
}

int DigitalWallet::viewBalance(QString address) {
    // Find the user in the map using the provided address
    auto it = mapOfUsers.find(address);

    return (it->second).balance;

}

void DigitalWallet::editProfile(QString address) {
    int choice;
    QString response;
    QString newname;
    QString newpassword;
    QString newemail;
    QString newphonenumber;

    auto it = mapOfUsers.find(address);
    if (it == mapOfUsers.end()) {
        QMessageBox::information(nullptr, "Error", "No user found with the specified address.");
        return;
    }

    do {
        // Display editing options
        choice = QInputDialog::getInt(nullptr, "Edit Profile", "Select the data you want to edit:\n1. Name\n2. Password\n3. Email\n4. Phone Number\n5. Back to main menu");

        switch (choice) {
        case 1:
            newname = QInputDialog::getText(nullptr, "Edit Profile", "Enter new name:");
            (it->second).name = newname;
            QMessageBox::information(nullptr, "Edit Profile", "Name updated successfully.");
            response = QInputDialog::getText(nullptr, "Edit Profile", "Do you want to edit another data? (Press 1 to continue)");
            break;

        case 2:
            newpassword = QInputDialog::getText(nullptr, "Edit Profile", "Enter new password:");
            (it->second).password = Hash(newpassword);
            QMessageBox::information(nullptr, "Edit Profile", "Password updated successfully.");
            response = QInputDialog::getText(nullptr, "Edit Profile", "Do you want to edit another data? (Press 1 to continue)");
            break;

        case 3:
            newemail = QInputDialog::getText(nullptr, "Edit Profile", "Enter new email:");
            (it->second).email = newemail;
            QMessageBox::information(nullptr, "Edit Profile", "Email updated successfully.");
            response = QInputDialog::getText(nullptr, "Edit Profile", "Do you want to edit another data? (Press 1 to continue)");
            break;

        case 4:
            newphonenumber = QInputDialog::getText(nullptr, "Edit Profile", "Enter new phone number:");
            (it->second).phone_number = newphonenumber;
            QMessageBox::information(nullptr, "Edit Profile", "Phone number updated successfully.");
            response = QInputDialog::getText(nullptr, "Edit Profile", "Do you want to edit another data? (Press 1 to continue)");
            break;

        case 5:
            response = "0"; // Exit loop
            break;

        default:
            QMessageBox::warning(nullptr, "Edit Profile", "Please choose a valid option.");
            response = "1";
            break;
        }

    } while (response == "1");
}

