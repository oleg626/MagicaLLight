<<<<<<< HEAD
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

void MainWindow::on_pushButton_clicked()
{
//    QString filename = QFileDialog::getOpenFileName(
//                this,
//                tr("Open File"),
//                "C:/Users/oleg6/Videos/Any Audio Converter/WAVE",
//                "All files (*.*);;Wav files (*.wav)"

//                );
//    QMessageBox::information(this,"file name",filename);
}



void MainWindow::on_start_button_clicked()
{
    ui->working_label->setText("Light is working!");
}

void MainWindow::on_stop_button_clicked()
{
    ui->working_label->setText("Light is not working :c");
}
=======
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

void MainWindow::on_pushButton_clicked()
{
//    QString filename = QFileDialog::getOpenFileName(
//                this,
//                tr("Open File"),
//                "C:/Users/oleg6/Videos/Any Audio Converter/WAVE",
//                "All files (*.*);;Wav files (*.wav)"

//                );
//    QMessageBox::information(this,"file name",filename);
}



void MainWindow::on_start_button_clicked()
{
    ui->working_label->setText("Light is working!");
}

void MainWindow::on_stop_button_clicked()
{
    ui->working_label->setText("Light is not working :c");
}
>>>>>>> 563b9ef6e74732dbe513e6f8379036a801268e84
