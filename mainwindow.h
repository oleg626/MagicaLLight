#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "server.h"
#include <QMainWindow>
#include <QtSql/QSqlTableModel>
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
    void createUI(const QStringList &headers);
    void on_start_button_clicked();
    void lights_connected();
    //void lights_disconnected();
    void on_stop_button_clicked();
    void on_browse_button_clicked();

    void on_AddSong_clicked();

    void on_DeleteSong_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

