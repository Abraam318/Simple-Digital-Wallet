#ifndef FILES_H
#define FILES_H

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDataStream>
#include <QVector>
#include "DigitalWallet.h"

class DigitalWallet;


class Files {
public:
    void readfrom(std::unordered_map<QString, DigitalWallet::User>& mapOfUsers);
    void saveTo(std::unordered_map<QString, DigitalWallet::User>& mapOfUsers);
    void readfromTrans(std::vector<DigitalWallet::Transaction>& transactions);
    void saveToTrans(std::vector<DigitalWallet::Transaction>& transactions);
    void readfromNot(std::vector<DigitalWallet::Transaction>& RequestHistory);
    void saveToNot(std::vector<DigitalWallet::Transaction>& RequestHistory);
    void Save(std::unordered_map<QString, DigitalWallet::User>& mapOfUsers, std::vector<DigitalWallet::Transaction>& transactions, std::vector<DigitalWallet::Transaction>& RequestHistory);
    void Read(std::unordered_map<QString, DigitalWallet::User>& mapOfUsers, std::vector<DigitalWallet::Transaction>& transactions, std::vector<DigitalWallet::Transaction>& RequestHistory);
};

#endif // FILES_H
