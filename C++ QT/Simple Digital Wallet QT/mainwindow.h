#ifndef MAINWINDOW_H

#define MAINWINDOW_H


#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_16_clicked();

    void on_ok_3_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_5_clicked();

    void on_ok_2_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_22_clicked();

    void on_ok_5_clicked();

    void on_ok_4_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_ok_9_clicked();

    void on_ok_10_clicked();

    void on_ok_11_clicked();


private slots:
    void handleLogin(bool success);

    void on_label_20_linkActivated(const QString &link);

    void on_label_10_linkActivated(const QString &link);

    void on_label_21_linkActivated(const QString &link);

    void on_pushButton_24_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_28_clicked();

    void on_ok_7_clicked();

    void on_ok_6_clicked();

    void on_pushButton_29_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
