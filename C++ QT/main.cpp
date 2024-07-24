#include "mainwindow.h"
#include "DigitalWallet.h"
#include <QApplication>
#include <QObject>
#include <QLocale>
#include <QTranslator>
#include "DigitalWallet.h"

void myExitFunction() {

    DigitalWallet wallet;
    wallet.fin();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "finalds_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    MainWindow w;
    DigitalWallet wallet;
    QObject::connect(&a, &QApplication::destroyed, &myExitFunction);
    wallet.init();
    w.show();
    return a.exec();
}

