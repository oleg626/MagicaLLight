#include "mainwindow.h"
#include <QApplication>
#include "server.h"
#include "QFile"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile styleF;

    styleF.setFileName("C:/Users/oleg6/Documents/MagicaLLights/style.css");
    styleF.open(QFile::ReadOnly);
    QString qssStr = styleF.readAll();

    //qApp->setStyleSheet(qssStr);
    MainWindow w;
    w.show();


    return a.exec();
}
