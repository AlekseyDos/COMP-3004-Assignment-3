#ifndef ELEVATORCONTROLSYSTEM_H
#define ELEVATORCONTROLSYSTEM_H

#include "defs.h"
#include "elevator.h"

class ElevatorControlSystem : public QObject
{
    Q_OBJECT
public:
    ElevatorControlSystem();

    void assignElevatorLabels(QLabel *label1, QLabel *label2, QLabel *label3);
    void setupUI(QLineEdit *ele1DS, QLineEdit *ele1MS, QLineEdit *ele1AL, QLineEdit *ele2DS, QLineEdit *ele2MS, QLineEdit *ele2AL, QLineEdit *ele3DS, QLineEdit *ele3MS, QLineEdit *ele3AL);

public slots:
    void floorCall(int floor, int direction);
    void pannelCall(int floor, int eleNum);
    void elevatorStopped(int id);
    void closeDoorButton(int eleNum, bool checked);
    void openDoorButton(int eleNum, bool checked);
    void helpAlarm(int eleNum, bool checked);
    void alarms(QString text, bool checked);
    void overload(int eleNum, bool checked);
    void obstical(int eleNum, bool checked);

signals:
    void moveElevator1(QList<int> *destinations);
    void moveElevator2(QList<int> *destinations);
    void moveElevator3(QList<int> *destinations);

private:
    Elevator ele1, ele2, ele3;
    Elevator *elevators[3] = {&ele1, &ele2, &ele3};
    QThread _Ele1thread, _Ele2thread, _Ele3thread;
    QList<int> ele1DestinationsUp, ele1DestinationsDown, ele2DestinationsUp, ele2DestinationsDown, ele3DestinationsUp, ele3DestinationsDown;
    int safeFloor;
    bool ele1AlarmActive, ele2AlarmActive, ele3AlarmActive;

};

#endif // ELEVATORCONTROLSYSTEM_H
