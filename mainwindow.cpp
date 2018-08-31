#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QMessageBox"
#include "server.h"
#include "QPushButton"
#include "QCheckBox"
#include "Qt"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::Server.startServer();
    connect(&(MainWindow::Server),
            SIGNAL(newConnection()),
            this,
            SLOT(lights_connected()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::lights_connected()
{
    ui->lightConnected_checkBox->setCheckable(true);
    qDebug()<<"Lights connected";
    ui->lightConnected_checkBox->setChecked(true);
    //ui->lightConnected_checkBox->setCheckable(false);
}

void MainWindow::on_start_button_clicked()
{
    if(ui->lightConnected_checkBox->isChecked())
    {
        if(ui->blinking_radioButton->isChecked())
        {
            MainWindow::Server.socket->write("blinking");
        }
        else if(ui->breathing_radioButton->isChecked())
        {
            MainWindow::Server.socket->write("breathing");
        }
        else if(ui->magic_radioButton->isChecked())
        {
            MainWindow::Server.socket->write("magic");
            MainWindow::Server.first_time = true;
            MainWindow::Server.times_called = 0;
        }
        else
        {
            QMessageBox::information(this,"Follow steps","Choose the mode");
        }
        ui->centralWidget->setStyleSheet(
        "#centralWidget {background-image: url(:/background-image/images/bg/on_ready.png);}");
    }
    else
    {
        QMessageBox::warning(this,"Error","Light's not connected");
    }


}

void MainWindow::on_stop_button_clicked()
{
    ui->centralWidget->setStyleSheet("#centralWidget {background-image: url(:/background-image/images/bg/off_ready.png);}");
    MainWindow::Server.socket->write("stop");
    MainWindow::Server.player->stop();
    MainWindow::Server.times_called = 0;
}


void MainWindow::on_browse_button_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C:/Users/oleg6/Videos/Any Audio Converter/WAVE/",
                "All files (*.*);; Wav files (*.wav)"

                );
    ui->file_name_lineEdit->setText(filename);
    MainWindow::Server.putii = &filename;
    MainWindow::Server.prepareSong(filename);
    qDebug()<<"Let's play some music";
    QUrl adresok = (QFileInfo(*MainWindow::Server.putii).absoluteFilePath());
    MainWindow::Server.player->setMedia(adresok);
    qDebug()<<MainWindow::Server.player->errorString();
}







