#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <QString>
#include "DigitalWallet.h" // Include the full definition of DigitalWallet
#include "Files.h"

QString path = "C:/Users/Abraam Adel/Downloads/Compressed/DS/user.csv";
QString pathT = "C:/Users/Abraam Adel/Downloads/Compressed/DS/trans.csv";
QString pathN = "C:/Users/Abraam Adel/Downloads/Compressed/DS/not.csv";

void Files::readfrom(std::unordered_map<QString, DigitalWallet::User>& mapOfUsers) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for reading:" << path;
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList tokens = line.split(',');

        if (tokens.size() == 8) {
            DigitalWallet::User user;
            user.name = tokens[1];
            user.balance = tokens[2].toDouble();
            user.password = tokens[3];
            user.email = tokens[4];
            user.phone_number = tokens[5];
            user.isAdmin = (tokens[6] == "true");
            user.isActive = (tokens[7] == "true");

            mapOfUsers[tokens[0]] = user;
        } else {
            qDebug() << "Invalid line format:" << line;
        }
    }

    file.close();
}

void Files::saveTo(std::unordered_map<QString, DigitalWallet::User>& mapOfUsers) {
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for writing:" << path;
        return;
    }

    QTextStream out(&file);
    for (const auto& pair : mapOfUsers) {
        const DigitalWallet::User& user = pair.second;
        out << pair.first << "," << user.name << "," << user.balance << ","
            << user.password << "," << user.email << "," << user.phone_number << ","
            << (user.isAdmin ? "true" : "false") << "," << (user.isActive ? "true" : "false") << Qt::endl;
    }

    file.close();
}

void Files::readfromTrans(std::vector<DigitalWallet::Transaction>& transactions) {
    QFile file(pathT);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for reading:" << pathT;
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList tokens = line.split(',');

        if (tokens.size() == 6) {
            DigitalWallet::Transaction trans;
            trans.SAddress = tokens[0];
            trans.RAddress = tokens[1];
            trans.amount = tokens[2].toDouble();
            trans.Accepted = (tokens[3] == "true");
            trans.PendigStatus = tokens[4].toInt();
            trans.Type = tokens[5];

            transactions.push_back(trans);
        } else {
            qDebug() << "Invalid line format:" << line;
        }
    }

    file.close();
}

void Files::saveToTrans(std::vector<DigitalWallet::Transaction>& transactions) {
    QFile file(pathT);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for writing:" << pathT;
        return;
    }

    QTextStream out(&file);
    for (const auto& trans : transactions) {
        out << trans.SAddress << "," << trans.RAddress << "," << trans.amount << ","
            << (trans.Accepted ? "true" : "false") << "," << trans.PendigStatus << ","
            << trans.Type << Qt::endl;
    }
    file.close();
}

void Files::readfromNot(std::vector<DigitalWallet::Transaction>& RequestHistory) {
    QFile file(pathN);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for reading:" << pathN;
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList tokens = line.split(',');

        if (tokens.size() == 7) {

            DigitalWallet::Transaction trans;
            trans.SAddress = tokens[0];
            trans.RAddress = tokens[1];
            trans.amount = tokens[2].toDouble();
            trans.Accepted = (tokens[3] == "true");
            trans.PendigStatus = tokens[4].toInt();
            trans.Type = tokens[5];
            trans.id  = tokens[6].toInt();
            RequestHistory.push_back(trans);
        } else {
            qDebug() << "Invalid line format:" << line;
        }
    }

    file.close();
}

void Files::saveToNot(std::vector<DigitalWallet::Transaction>& RequestHistory) {
    QFile file(pathN);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for writing:" << pathN;
        return;
    }

    QTextStream out(&file);
    for (const auto& trans : RequestHistory) {
        out << trans.SAddress << "," << trans.RAddress << "," << trans.amount << ","
            << (trans.Accepted ? "true" : "false") << "," << trans.PendigStatus << ","
            << trans.Type << "," << trans.id << Qt::endl;
    }
    file.close();
}

void Files::Save(std::unordered_map<QString, DigitalWallet::User>& mapOfUsers, std::vector<DigitalWallet::Transaction>& transactions, std::vector<DigitalWallet::Transaction>& RequestHistory){
    saveTo(mapOfUsers);
    saveToTrans(transactions);
    saveToNot(RequestHistory);
}

void Files::Read(std::unordered_map<QString, DigitalWallet::User>& mapOfUsers, std::vector<DigitalWallet::Transaction>& transactions, std::vector<DigitalWallet::Transaction>& RequestHistory){
    readfrom(mapOfUsers);
    readfromTrans(transactions);
    readfromNot(RequestHistory);
}
