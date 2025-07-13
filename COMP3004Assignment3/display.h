#ifndef DISPLAY_H
#define DISPLAY_H

#include <QObject>
#include <QtDebug>
#include <QLineEdit>

class Display : public QObject
{
    Q_OBJECT
public:
    Display();

    void setLineEdit(QLineEdit *lineEdit);

    void displayMessage(QString text);

private:
    QLineEdit *displayText;
};

#endif // DISPLAY_H
