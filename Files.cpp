#include "Files.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "DigitalWallet.h"
#include <queue>
using namespace std;

string path = "D:\\FCIS26\\Second Year\\DS project\\untitled\\user.csv";
string pathT = "D:\\FCIS26\\Second Year\\DS project\\untitled\\trans.csv";
string pathN = "D:\\FCIS26\\Second Year\\DS project\\untitled\\not.csv";

//string path =  "C:\\Users\\merna\\OneDrive - Faculty of Computer and Information Sciences (Ain Shams University)\\Documents\\Final_Console\\user.csv";
//string pathT = "C:\\Users\\merna\\OneDrive - Faculty of Computer and Information Sciences (Ain Shams University)\\Documents\\Final_Console\\trans.csv";
//string pathN = "C:\\Users\\merna\\OneDrive - Faculty of Computer and Information Sciences (Ain Shams University)\\Documents\\Final_Console\\not.csv";

void Files::readfrom(unordered_map<string, DigitalWallet::User>& mapOfUsers) {

    ifstream file(path);
    string line;

    if (!file.is_open())
    {
        cerr << "Could not open file: " << path << endl;
        return;
    }
    while (getline(file, line)) {
        istringstream iss(line);
        DigitalWallet::User user;
        string add;

        vector<string> tokens;
        string token;
        while (getline(iss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() == 8) {
            add = tokens[0];
            user.name = tokens[1];
            user.balance = stod(tokens[2]);
            user.password = tokens[3];
            user.email = tokens[4];
            user.phone_number = tokens[5];

            // Convert isAdmin and isActive strings to bool
            user.isAdmin = (tokens[6] == "true") ? true : false;
            user.isActive = (tokens[7] == "true") ? true : false;

            mapOfUsers[add] = user;
        }
        else {
            cerr << "Invalid line format: " << line << endl;
        }
    }

    file.close();

    ofstream clearFile(path, ofstream::out | ofstream::trunc);
    clearFile.close();
}
void Files::saveTo(unordered_map<string, DigitalWallet::User>& mapOfUsers) {
    ofstream file(path, std::ios::app);

    if (!file.is_open()) {
        cerr << "Could not open this file" << endl;
        return;
    }

    for (const auto& pair : mapOfUsers) {
        const DigitalWallet::User& user = pair.second;
        file << pair.first << ","
             << user.name << ","
             << user.balance << ","
             << user.password << ","
             << user.email << ","
             << user.phone_number << ","
             << (user.isAdmin ? "true" : "false") << ","
             << (user.isActive ? "true" : "false") << endl;
    }

    file.close();
}

void Files::readfromTrans(vector<DigitalWallet::Transaction>& transactions) {
    ifstream file(pathT);
    string linetext;
    if (!file.is_open())
    {
        cerr << "Could not open this file" << endl;
        return;
    }
    while (getline(file, linetext)) {
        stringstream ss(linetext);
        string token;

        DigitalWallet::Transaction transinput;

        // Parse the line using commas as delimiters
        getline(ss, transinput.SAddress, ',');
        getline(ss, transinput.RAddress, ',');
        ss >> transinput.amount;
        ss.ignore();

        getline(ss, transinput.Type);


        transactions.push_back(transinput);
    }
    file.close();
}
void Files::saveToTrans(vector<DigitalWallet::Transaction>& transactions) {
    ofstream file(pathT);

    if (!file.is_open()) {
        cerr << "Could not open the file" << endl;
        return;
    }

    for (const auto& trans : transactions) {
        file << trans.SAddress << ","
             << trans.RAddress << ","
             << trans.amount << ","

             << trans.Type << "\n";
    }

    file.close();
}

void Files::readfromNot(vector<DigitalWallet::Transaction>& RequestHistory) {
    ifstream file(pathN);
    string linetext;
    if (!file.is_open())
    {
        cerr << "Could not open this file" << endl;
        return;
    }
    while (getline(file, linetext)) {
        stringstream ss(linetext);
        string token;

        DigitalWallet::Transaction transinput;


        getline(ss, transinput.SAddress, ',');
        getline(ss, transinput.RAddress, ',');
        ss >> transinput.amount;
        ss.ignore();

        getline(ss, transinput.Type);

        RequestHistory.push_back(transinput);
    }
    file.close();
}
void Files::saveToNot(vector<DigitalWallet::Transaction>& RequestHistory) {
    ofstream file(pathN);

    if (!file.is_open()) {
        cerr << "Could not open the file" << endl;
        return;
    }

    for (const auto& trans : RequestHistory) {
        file << trans.SAddress << ","
             << trans.RAddress << ","
             << trans.amount << ","

             << trans.Type << "\n";
    }

    file.close();
}
