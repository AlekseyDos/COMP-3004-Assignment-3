#ifndef DOOR_H
#define DOOR_H

#include <QObject>
#include <QtDebug>
#include <QLineEdit>

class Door : public QObject
{
    Q_OBJECT
public:
    Door();

    void setLineEdit(QLineEdit *lineEdit);

    void open();
    void close();

private:
    QLineEdit *doorText;
};

#endif // DOOR_H
