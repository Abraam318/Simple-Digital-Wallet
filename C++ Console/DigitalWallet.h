#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class DigitalWallet {
public:
    struct Transaction {
        string SAddress;
        string RAddress;
        double amount;
        string Type;
    };

    struct User {
        string name;
        double balance = 0;
        string password;
        string email;
        string phone_number;
        bool isAdmin = false;
        bool isActive = true;
    };

    vector<Transaction> transactions;
    vector<Transaction> RequestHistory;

public: unordered_map<string, User> mapOfUsers;

    void delay(int milliseconds);
    void init();
    bool isadmin(string address);
    void Send(string SAddress, string RAddress, double amount);
    void Req(string SA, string RA, double amount);
    void MyHistory(string SAddress);
    void notification(string Address);
    bool withdrawal(string address, double amount);
    void deposit(string address, double amount);
    bool login(string address, string password);
    void signUp(string address, string name, string phone_number, string email, string password);
    void viewBalance(string address);
    void editProfile(string address);
    string Hash(const string& password);
    string maskedInput();

};