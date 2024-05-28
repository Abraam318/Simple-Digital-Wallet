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
        bool Accepted = false;
        int PendigStatus = -1; // is pending
        string Type;
    };

    struct User {
        string name;
        double balance = 0;
        string password;
        string email;
        string phone_number;
        bool isAdmin = false;
        bool isActive = true; // New attribute to track account status
    };

    int TransactionCounter =0;
    int response = 0;
    vector<Transaction> transactions;
    vector<Transaction> History;
    vector<Transaction> RequestHistory;
    unordered_map<string, User> mapOfUsers;

    void delay(int milliseconds);
    void init();
    bool isadmin(string address);
    void Send(string SAddress, string RAddress, double amount);
    void AddRec(Transaction tra);
    void Req(string SA, string RA, double amount);
    void MyHistory(string SAddress);
    void notification();
    bool withdrawal(string address, double amount);
    void deposit(string address, double amount);
    bool login(string address, string password);
    void signUp(string address, string name, string phone_number, string email, string password);
    void viewBalance(string address);
    void editProfile(string address);
    string Hash(const string& password);
};