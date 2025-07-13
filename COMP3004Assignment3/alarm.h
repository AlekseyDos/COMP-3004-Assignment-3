#ifndef ALARM_H
#define ALARM_H

#include <QObject>
#include <QtDebug>
#include <QLineEdit>

class Alarm : public QObject
{
    Q_OBJECT
public:
    Alarm();

    void setLineEdit(QLineEdit *lineEdit);

    void setAlarm(QString text);

private:
    QLineEdit *alarmText;
};

#endif // ALARM_H
