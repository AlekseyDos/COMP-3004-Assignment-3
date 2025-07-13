#include "alarm.h"

Alarm::Alarm() {}

//assigns the ui element to the alarm
void Alarm::setLineEdit(QLineEdit *lineEdit) { alarmText = lineEdit; }

void Alarm::setAlarm(QString text)
{
    alarmText->setText(text);
    qDebug() << "ALARM:" << text;
}
