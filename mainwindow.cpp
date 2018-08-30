#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QMessageBox"
#include "server.h"
#include "QPushButton"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::Server.startServer();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_start_button_clicked()
{
    ui->centralWidget->setStyleSheet("#centralWidget {background-image: url(:/background-image/images/bg/on_ready.png);}");
}

void MainWindow::on_stop_button_clicked()
{
    ui->centralWidget->setStyleSheet("#centralWidget {background-image: url(:/background-image/images/bg/off_ready.png);}");
}

