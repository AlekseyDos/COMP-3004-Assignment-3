#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QLabel>
#include <QThread>
#include <QList>
#include "sensor.h"
#include "door.h"
#include "display.h"
#include "alarm.h"

class Elevator : public QObject
{
    Q_OBJECT
public:
    Elevator();

    void assignElevatorLabel(QLabel *label);
    void assignElevatorID(int eid);

    int getDirection();
    int getFloorDirection(int floor);

    void setDoorButtonState(int btn, bool checked);
    void setupUI(QLineEdit *eleDS, QLineEdit *eleMS, QLineEdit *eleAL);
    void setAlarm(QString text);
    void setOverload(bool checked);
    void setObstical(bool checked);

    int checkFloorDistance(int floor);

public slots:
    void moveElevator(QList<int> *destinations);

signals:
    void elevatorStopped(int id);

private:
    QLabel *eleLabel;
    Sensor sens;
    Door door;
    Display display;
    Alarm alarm;
    bool closeDoor, openDoor, overload, obstical;
    int direction;
    int id;


};

#endif // ELEVATOR_H
