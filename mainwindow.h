<<<<<<< HEAD
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "server.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    myserver Server;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_start_button_clicked();

    void on_stop_button_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
=======
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "server.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    myserver Server;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_start_button_clicked();

    void on_stop_button_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
>>>>>>> 563b9ef6e74732dbe513e6f8379036a801268e84
