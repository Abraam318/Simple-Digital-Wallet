#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "DigitalWallet.h"
#include <queue>
#include <stdexcept>
using namespace std;


class Files {

    public: void readfrom(unordered_map<string, DigitalWallet::User>& mapOfUsers);
    public: void saveTo(unordered_map<string, DigitalWallet::User>& mapOfUsers);

    public: void readfromTrans(vector<DigitalWallet::Transaction>& transactions);
    public: void saveToTrans(vector<DigitalWallet::Transaction>& transactions);

    public: void readfromNot(vector<DigitalWallet::Transaction>& RequestHistory);
    public: void saveToNot(vector<DigitalWallet::Transaction>& RequestHistory);

};