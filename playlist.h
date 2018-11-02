#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <QTableWidget>
#include <QTableWidgetItem>

class playlist: public QTableWidget
{
    Q_OBJECT
public:
    playlist();
    ~playlist();
    int number_of_elements;
};

#endif // PLAYLIST_H
