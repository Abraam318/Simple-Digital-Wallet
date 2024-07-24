#pragma once
#ifndef DIGITALWALLET_H
#define DIGITALWALLET_H

#include <QString>
#include <vector>

using namespace std;


class DigitalWallet {
public:
    struct Transaction {
        QString SAddress;
        QString RAddress;
        double amount;
        bool Accepted = false;
        int PendigStatus = -1;
        QString Type;
        int id;
    };
    struct User {
        QString name;
        double balance = 0;
        QString password;
        QString email;
        QString phone_number;
        bool isAdmin = false;
        bool isActive = true;
    };


    void init();
    void fin();
    void Send(QString SAddress, QString RAddress, double amount);
    void MyHistory(QString SAddress);
    void notification(QString Address);
    void Req(QString SA, QString RA, double amount);
    bool withdrawal(QString address, double amount);
    void deposit(QString address, double amount);
    int login(QString &CurrentUser, QString address, QString password);
    bool signUp(QString address, QString name, QString phone_number, QString email, QString password,bool admin);
    int viewBalance(QString address);
    void editProfile(QString address);
    vector<Transaction> gettrans();
    unordered_map<QString,User> getusers();
    vector<Transaction> gethistory();
    QString Hash(const QString& password);
    int getnotcnt();
    void setnotcnt(int x);
    void EditHis(int id);
    bool Edit(QString address, QString name, QString phone_number, QString email, QString password);
/*signals:
    void loggedIn(bool success);*/
};

#endif // DIGITALWALLET_H
