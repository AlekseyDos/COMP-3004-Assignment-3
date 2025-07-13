#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include <QtDebug>
#include <QPoint>

class Sensor : public QObject
{
    Q_OBJECT
public:
    Sensor();

    int atFloor(QPoint pos, int floor);
    int distance(QPoint pos, int floor);
    int currFloor(QPoint pos);

private:
    QPoint floor1, floor2, floor3, floor4, floor5, floor6, floor7;
    QPoint floors[7] = {floor1, floor2, floor3, floor4, floor5, floor6, floor7};
};

#endif // SENSOR_H
