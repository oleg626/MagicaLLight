#include <server.h>
#include <QMediaPlayer>
#include <QFileInfo>
#include <QtEndian>
#include <mem.h>
#include <QString>
#include <Qtime>


#define K 4

myserver::myserver()
{
    player = new QMediaPlayer(this);
    myserver::putii = new QString("C:/Users/oleg6/Videos/Any Audio Converter/WAVE/aida.wav");
}

myserver::~myserver(){}

qint16 myserver::filter(qint16 input)
{
    static qint16 D = 0;
    static qint16 out = 0;//выходное значение фильтра
    D = D + input - out;
    out = D/(qint16)K;
    return out;
}

void myserver::startServer()
{
    if(this->listen(QHostAddress::Any,5555))
    {
        qDebug()<<"Listening";
    }
    else
    {
        qDebug()<<"Not listening";
    }
}

void myserver::sendData(char * Data)
{
    if(socket->isOpen())
    {
        socket->write(Data);
        qDebug()<<"sent";
    }
}
void myserver::prepareSong(QString filename)
{
    QFile file(*myserver::putii);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }
    // пропуск чтения хидера, считаем что это 44100КГц, 16 бит, 2 канала

    // ищем data
    quint32 chunkDataSize = 0;

    QByteArray temp_buff;//Кусочек данных
    char buff[0x04];//массив
    while (true)
    {
        QByteArray tmp = file.read(0x04);//Считываем 4 байта из .wav файла
        temp_buff.append(tmp);//Добавляем их в конец массива
        int idx = temp_buff.indexOf("data");//Определяем, сколько элементов занимает заголовок
        if (idx >= 0)//Если слово "data" встретилось
        {
            int lenOfData = temp_buff.length() - (idx + 4);//определеяем
            memcpy(buff, temp_buff.constData() + idx + 4, lenOfData);
            int bytesToRead = 4 - lenOfData;
            // дочитываем длину чанков
            if (bytesToRead > 0)
            {
                int read = file.read(buff + lenOfData, bytesToRead);
                if (bytesToRead != read)
                {
                    qDebug() << "something awful happens";
                    return;
                }
            }
            chunkDataSize = qFromLittleEndian<quint32>((const uchar*)buff);
            break;
        }
        if (temp_buff.length() >= 8)
        {
            temp_buff.remove(0, 0x04);
        }
    }
    if (!chunkDataSize)
    {
        qDebug() << "chunk data not found";
        return;
    }
    qDebug() << "length of chunks =" << chunkDataSize;
    int samples = 0;
    static int counter = 0;
    while (file.read(buff, 0x04) > 0)
    {
        chunkDataSize -= 4;
        //qint16 ch1 = qFromLittleEndian<qint16>((const uchar*)buff);
       //qint16 ch2 = qFromLittleEndian<qint16>((const uchar*)buff);

        if(counter%4800==0)
        {
            myserver::channel1[samples] = myserver::filter(abs(qFromLittleEndian<qint16>((const uchar*)buff))/4);
            //qDebug()<<myserver::channel1[samples]<<endl;
            if(myserver::channel1[samples] > myserver::maximum)
            {
                myserver::maximum = myserver::channel1[samples];
            }
            //myserver::channel2[samples] = qFromLittleEndian<qint16>((const uchar*)buff);
            samples++;
        }
        counter++;
        // проверка на окончание
        if (chunkDataSize == 0 || chunkDataSize & 0x80000000) {
            break;
        }
    }
    myserver::samples_amount = samples;
    myserver::times_called = 0;
    float divider = (float) myserver::maximum/1023;
    for(int i = 0; i<myserver::samples_amount;i++)
    {
        myserver::channel1[i]/=divider;
    }
    qint16 max = 1023;
    qint16 min = 0;
    for(int i = 0;i<myserver::samples_amount; i++)
    {
        //qDebug()<<myserver::channel1[i]<<" ";
        max--;
        min++;
        if(myserver::channel1[i] > max)
        {
            max = myserver::channel1[i];
            myserver::channel1[i]=1023;
        }
        else if(myserver::channel1[i]<min)
        {
            min = myserver::channel1[i];
            myserver::channel1[i] = 0;
        }
        else
        {
            if((max-min)!=0)
            {
                float temp = (float)(myserver::channel1[i]-min)/(max-min);
                //qDebug()<<"temp "<<temp;
                myserver::channel1[i] = (qint16)(temp*1023);
                //qDebug()<<myserver::channel1[i];
            }
            else
            {
                qDebug()<<"got";
                max++;
                min--;
                float temp = (float)(myserver::channel1[i]-min)/(max-min);
                myserver::channel1[i] = (qint16)(temp*1023);
                qDebug()<<myserver::channel1[i];
            }
        }}

    qDebug()<<myserver::maximum<<endl;
    qDebug() << "readed" << samples << "samples";
    for(int i = 0;i<myserver::samples_amount; i++)
    {
        std::string s = std::to_string(myserver::channel1[i]);
        char const *pchar = s.c_str();
        myserver::channel1_char[i] = pchar;
    }
}
void myserver::incomingConnection(int socketDescriptor)
{
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);
//////////////////////////////////////
    connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));

    QUrl adresok = (QFileInfo(*myserver::putii).absoluteFilePath());
    player->setMedia(adresok);
    qDebug()<<player->errorString();
    qDebug()<<socketDescriptor<<" Client connected";
}


void myserver::sockReady()
{
    static bool start = true;
    if(start)
    {
        player->play();
        start = false;
    }
    std::string s = std::to_string(myserver::channel1[myserver::times_called]);
    char const *pchar = s.c_str();
    socket->write(pchar);
    myserver::times_called++;
    if(myserver::times_called == myserver::samples_amount)
    {
        //player->play();
        //timer->stop();
        qDebug()<<"Finished";
        socket->write("finished");
        myserver::times_called=0;
    }
}

void myserver::sockDisc()
{
    qDebug()<<"Disconnect";
    socket->deleteLater();
}
