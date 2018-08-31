#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QMediaPlayer>
#include <QAudioDecoder>
#include <QDebug>
#include <QTimer>
class myserver: public QTcpServer
{
    Q_OBJECT
public:
    myserver();
    ~myserver();
    qint16 filter(qint16 input);
    QTcpSocket* socket;
    qint16 channel1[10000];
    const char* channel1_char[10000];
    qint32 samples_amount=0;
    bool there_is_client = false;
    int times_called = 0;
    int maximum = 0;
    bool first_time = true;
    const QString *putii;
    qint64 maxlength = 1024;
    QMediaPlayer* player;

public slots:
    void sendData(char *);
    int prepareSong(QString filename);
    void startServer();
    void incomingConnection(int socketDescriptor);
    void sockReady();
    void sockDisc();
};

#endif // MYSERVER_H

