#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QMessageBox>
#include "DigitalWallet.h"

QString CurrentUser;
DigitalWallet a;

vector<DigitalWallet::Transaction> v;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_3_clicked()
{

    QString add =ui->loginAddress->text();
    QString pass =ui->loginPassword->text();

    if(add.isEmpty() || pass.isEmpty()){
        QMessageBox::warning(this, "Login Attemp", "Please Provide all the Data");
        return;
    }

    DigitalWallet a;
    int notifications = 0;

    switch (a.login(CurrentUser, add, pass)) {
    case 1:
        ui->stackedWidget->setCurrentIndex(2);
        ui->label_10->setText("Current balance: " + QString::number(a.viewBalance(CurrentUser)) + " LE");
        for (int i = 0; i < a.gethistory().size(); i++){
            if( a.gethistory()[i].RAddress == CurrentUser &&  a.gethistory()[i].PendigStatus== -1){
                notifications++;
            }
        }
        ui->label_20->setText(QString::fromStdString(std::to_string(notifications)));
        break;
    case 2:
        ui->stackedWidget->setCurrentIndex(11);

    default:
        break;
    }

}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_11_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_pushButton_12_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_13_clicked()
{
    QString add = ui->lineEdit_address_6->text();
    QString amountStr = ui->lineEdit_address_5->text();
    bool isValidAmount = false;
    double amount = amountStr.toDouble(&isValidAmount);

    if(add.isEmpty()) {
        // Address is empty
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid address.");
        return;
    }


    if(!isValidAmount || amount <= 0) {
        // Amount is not a valid number or <= 0
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid amount.");
        return;
    }

    DigitalWallet a;
    a.Send(CurrentUser, add, amount);
    ui->label_10->setText("Current balance: " + QString::number(a.viewBalance(CurrentUser)) + " LE");

}

void MainWindow::on_pushButton_14_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}



void MainWindow::on_pushButton_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_pushButton_15_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_pushButton_16_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_ok_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_17_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_7_clicked()
{

    ui->stackedWidget->setCurrentIndex(9);
    DigitalWallet a;
    v.clear();

    for (int i = 0; i < a.gethistory().size(); i++){
        if( a.gethistory()[i].RAddress == CurrentUser &&  a.gethistory()[i].PendigStatus== -1){
            v.push_back(a.gethistory()[i]);
        }
    }

    ui->Not->setRowCount(v.size());
    for (int i = 0; i < v.size(); ++i) {
        ui->Not->setItem(i,0,new QTableWidgetItem(v[i].SAddress));
        ui->Not->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(to_string(v[i].amount))));
        ui->Not->setItem(i,2,new QTableWidgetItem(v[i].id));
    }
    ui->label_20->setText(QString::fromStdString(std::to_string(v.size())));

}

void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(10);
}

void MainWindow::on_ok_2_clicked()
{
    DigitalWallet a;

    QString name =ui->lineEdit_6->text();
    QString address =ui->lineEdit_7->text();
    QString number =ui->lineEdit_8->text();
    QString email =ui->lineEdit_9->text();
    QString pass =ui->lineEdit_10->text();

    if(name.isEmpty() ||address.isEmpty() ||number.isEmpty() ||email.isEmpty() ||pass.isEmpty() ){
        QMessageBox::warning(this, "SignUp Attemp", "Please provide all required Data");
        return;
    }

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Name Check", "Name is empty");
    }

    if (address.isEmpty()) {
        QMessageBox::warning(this, "Address Check", "Address is empty");
    }


    if(a.signUp(address, name, number, email, pass,0)){
        ui->stackedWidget->setCurrentIndex(1);

    }

}

void MainWindow::on_pushButton_18_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_19_clicked()
{
    double amount =  ui->lineEdit_address_7->text().toDouble();
    if(amount <= 0 ){
        QMessageBox::warning(this, "Deposite Failed", "Invalid amount.");
        return;
    }
    a.deposit(CurrentUser,amount);
    QMessageBox::information(this, "Deposite Successful", "Money added to your balance successfully.");
    ui->label_10->setText("Current balance: " + QString::number(a.viewBalance(CurrentUser)) + " LE");
    ui->stackedWidget->setCurrentIndex(2);


}

void MainWindow::on_pushButton_22_clicked()
{
    ui->stackedWidget->setCurrentIndex(12);
}

void MainWindow::on_ok_4_clicked()  /// Sign Up for Admin
{
    QString name =ui->lineEdit_11->text();
    QString address =ui->lineEdit_12->text();
    QString number =ui->lineEdit_13->text();
    QString email =ui->lineEdit_14->text();
    QString pass =ui->lineEdit_15->text();
    bool admin = ui->checkBox->isChecked();


    if(name.isEmpty() ||address.isEmpty() ||number.isEmpty() ||email.isEmpty() ||pass.isEmpty() ){
        QMessageBox::warning(this, "SignUp Attemp", "Please provide all required Data");
        return;
    }

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Name Check", "Name is empty");
    }

    if (address.isEmpty()) {
        QMessageBox::warning(this, "Address Check", "Address is empty");
    }

    if(a.signUp(address, name, number, email, pass,admin)){
        QMessageBox::information(this, "Account Creation", "Account added successfully");

    }


}

void MainWindow::on_pushButton_20_clicked()
{

    ui->History->setRowCount( a.gettrans().size());

    for (int i = 0; i <  a.gettrans().size(); ++i) {
        ui->History->setItem(i,0,new QTableWidgetItem( a.gettrans()[i].SAddress));
        ui->History->setItem(i,1,new QTableWidgetItem( a.gettrans()[i].RAddress));
        ui->History->setItem(i,2, new QTableWidgetItem(QString::fromStdString(to_string( a.gettrans()[i].amount))));
        ui->History->setItem(i,3,new QTableWidgetItem( a.gettrans()[i].Type));

    }
    ui->stackedWidget->setCurrentIndex(13);
}


void MainWindow::on_pushButton_23_clicked()
{
    DigitalWallet a;
    ui->stackedWidget->setCurrentIndex(14);

    ui->tableWidget_2->setRowCount(a.getusers().size());
    unordered_map<QString, DigitalWallet::User> usersMap = a.getusers();
    int row = 0;

    for (auto it = usersMap.begin(); it != usersMap.end(); ++it) {
        const DigitalWallet::User& user = it->second;

        ui->tableWidget_2->setItem(row, 0, new QTableWidgetItem(user.name));
        ui->tableWidget_2->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(to_string(user.balance))));
        ui->tableWidget_2->setItem(row, 2, new QTableWidgetItem(it->first));
        ui->tableWidget_2->setItem(row, 3, new QTableWidgetItem(user.email));
        ui->tableWidget_2->setItem(row, 4, new QTableWidgetItem(user.phone_number));
        ui->tableWidget_2->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(to_string(user.isAdmin))));
        ui->tableWidget_2->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(to_string(user.isActive))));

        row++;
    }
}


void MainWindow::on_pushButton_21_clicked()
{
    ui->stackedWidget->setCurrentIndex(15);
}

void MainWindow::on_ok_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(11);
}

void MainWindow::on_ok_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(11);
}

void MainWindow::on_ok_11_clicked()
{
    ui->stackedWidget->setCurrentIndex(11);
}


void MainWindow::handleLogin(bool success)
{
    if (success) {
        QMessageBox::information(this, "Login", "Login successful!");
        // Handle successful login
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid address or password.");
        // Handle login failure
    }
}


void MainWindow::on_ok_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(11);

    // Your implementation here...
    // This slot is called when a button with objectName "ok_5" is clicked
}



void MainWindow::on_label_20_linkActivated(const QString &link)
{

}


void MainWindow::on_label_10_linkActivated(const QString &link)
{
}


void MainWindow::on_label_21_linkActivated(const QString &link)
{

}


void MainWindow::on_pushButton_24_clicked()
{
    double amount =  ui->lineEdit_address_8->text().toDouble();
    if(amount <= 0 ){
        QMessageBox::warning(this, "Withdrawal Failed", "Invalid amount.");
        return;
    }
    a.withdrawal(CurrentUser,amount);
    ui->label_10->setText("Current balance: " + QString::number(a.viewBalance(CurrentUser)) + " LE");
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton_25_clicked()
{
    QString add = ui->lineEdit_address_4->text();
    double amount = ui->lineEdit_address_3->text().toDouble();
    a.Req(CurrentUser,add, amount);
}


void MainWindow::on_pushButton_26_clicked()
{
    int x = v[ui->lineEdit_address_15->text().toInt()-1].id;
    QString reciever;
    double amount;
    for (int i = 0; i < v.size(); ++i) {
        if(v[i].id==x){
            reciever = v[i].SAddress;
            amount = v[i].amount;
        }
    }
    a.Send(CurrentUser,reciever,amount);
    ui->label_10->setText("Current balance: " + QString::number(a.viewBalance(CurrentUser)) + " LE");

    a.EditHis(x);

    v.clear();

    for (int i = 0; i < a.gethistory().size(); i++){
        if( a.gethistory()[i].RAddress == CurrentUser &&  a.gethistory()[i].PendigStatus== -1){
            v.push_back(a.gethistory()[i]);
        }
    }
    ui->Not->setRowCount(v.size());

    ui->label_20->setText(QString::fromStdString(std::to_string(v.size())));

    for (int i = 0; i < v.size(); ++i) {
        ui->Not->setItem(i,0,new QTableWidgetItem(v[i].SAddress));
        ui->Not->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(to_string(v[i].amount))));
        ui->Not->setItem(i,2,new QTableWidgetItem(v[i].id));
    }
}


void MainWindow::on_pushButton_27_clicked()
{
    int x = v[ui->lineEdit_address_15->text().toInt()-1].id;
    a.EditHis(x);

    v.clear();

    for (int i = 0; i < a.gethistory().size(); i++){
        if( a.gethistory()[i].RAddress == CurrentUser &&  a.gethistory()[i].PendigStatus== -1){
            v.push_back(a.gethistory()[i]);
        }
    }
    ui->Not->setRowCount(v.size());
    ui->label_20->setText(QString::fromStdString(std::to_string(v.size())));

    for (int i = 0; i < v.size(); ++i) {
        ui->Not->setItem(i,0,new QTableWidgetItem(v[i].SAddress));
        ui->Not->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(to_string(v[i].amount))));
        ui->Not->setItem(i,2,new QTableWidgetItem(v[i].id));
    }

}

void MainWindow::on_pushButton_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    v.clear();

    for (int i = 0; i < a.gettrans().size(); i++){
        if( a.gettrans()[i].RAddress == CurrentUser || a.gettrans()[i].SAddress == CurrentUser){
            v.push_back(a.gettrans()[i]);
        }
    }

    ui->His->setRowCount(v.size());
    for (int i = 0; i < v.size(); ++i) {
        ui->His->setItem(i,0,new QTableWidgetItem(v[i].SAddress));
        ui->His->setItem(i,1,new QTableWidgetItem(v[i].RAddress));
        ui->His->setItem(i,2, new QTableWidgetItem(QString::fromStdString(to_string(v[i].amount))));
        ui->His->setItem(i,3,new QTableWidgetItem(v[i].Type));

    }

}

void MainWindow::on_pushButton_28_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

}


void MainWindow::on_ok_7_clicked()
{
    QString address = ui->lineEdit_31->text();
    unordered_map<QString, DigitalWallet::User> usersMap = a.getusers();
    for (auto it = usersMap.begin(); it != usersMap.end(); ++it) {
        if(it->first==address){
            ui->lineEdit_26->setText(it->second.name);
            ui->lineEdit_27->setText(it->first);
            ui->lineEdit_28->setText(it->second.phone_number);
            ui->lineEdit_29->setText(it->second.email);
        }
    }

}


void MainWindow::on_ok_6_clicked()
{
    QString name = ui->lineEdit_26->text();
    QString address = ui->lineEdit_27->text();
    QString email = ui->lineEdit_29->text();
    QString phone = ui->lineEdit_28->text();
    QString pass = ui->lineEdit_29->text();

    if(a.Edit(address,name,phone,email,pass))
    {
        QMessageBox::information(this, "Edit Data", "Edited successful!");

    }
}


void MainWindow::on_pushButton_29_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}

