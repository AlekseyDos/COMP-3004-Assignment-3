#include "elevator.h"

Elevator::Elevator()
{
    direction = 0;
    closeDoor = false;
    openDoor = false;
    overload = false;
    obstical = false;
}

//getter functions
int Elevator::getDirection() { return direction; }
int Elevator::getFloorDirection(int floor) { return sens.atFloor(eleLabel->pos(), floor); }

//setter functions
void Elevator::assignElevatorLabel(QLabel *label) { eleLabel = label; }
void Elevator::assignElevatorID(int eid) { id = eid; }
void Elevator::setOverload(bool checked) { overload = checked; }
void Elevator::setObstical(bool checked) { obstical = checked; }
void Elevator::setAlarm(QString text) { alarm.setAlarm(text); }

void Elevator::setDoorButtonState(int btn, bool checked)
{
    switch (btn) {

    case 1:
        closeDoor = checked;
        break;

    case 2:
        openDoor = checked;
        break;
    }
}

void Elevator::setupUI(QLineEdit *eleDS, QLineEdit *eleMS, QLineEdit *eleAL)
{
    door.setLineEdit(eleDS);
    display.setLineEdit(eleMS);
    alarm.setLineEdit(eleAL);

}

//controls the elevators navigation throughout the floors
void Elevator::moveElevator(QList<int> *destinations)
{
    if (destinations->isEmpty()) { return; }

    qDebug() << "Next floors for elevator " << eleLabel->text().back() << "are:" << *destinations;

    qDebug() << "Elevator" << eleLabel->text().back() << "moving to" << destinations->first();

    //update loop that moves the elevator to the next floor
    while ((sens.atFloor(eleLabel->pos(), destinations->first()) != 0))
    {
        //move the elevator up a floor
        if (sens.atFloor(eleLabel->pos(), destinations->first()) == 1)
        {
            eleLabel->move(eleLabel->x(), eleLabel->y() - 100);
            direction = 1;
        }

        //move the elevator down a floor
        else
        {
            eleLabel->move(eleLabel->x(), eleLabel->y() + 100);
            direction = 2;
        }

        //update the display with the current floor
        if (sens.currFloor(eleLabel->pos()) == 1) { display.displayMessage("G"); }
        else { display.displayMessage(QString::number(sens.currFloor(eleLabel->pos()))); }

        //represents the travel time between floors
        QThread::msleep(2000);
    }

    qDebug() << "Elevator" << eleLabel->text().back() << "arrived At Floor" << destinations->first();

    door.open();
    alarm.setAlarm("RING");

    //checks if the close door button is being pressed, otherwise waits 10 seconds
    for (int i = 0; i < 10; i++)
    {
        if (closeDoor) { break; }
        QThread::msleep(1000);
    }

    //checks for elevator overload or obstical blocking the door and waits for it to be cleared
    do
    {
        if (obstical)
        {
            alarm.setAlarm("OBSTICAL");
            display.displayMessage("OBSTICAL");
            qDebug() << "Elevator" << eleLabel->text().back() << "has an obstical in the way, please remove obstical.";

            QThread::msleep(5000);
        }

        else if (overload)
        {
            alarm.setAlarm("OVERLOAD");
            display.displayMessage("OVERLOAD");
            qDebug() << "Elevator" << eleLabel->text().back() << "is overloaded, please remove load.";

            QThread::msleep(5000);
        }
    }while (obstical || overload);

    //keeps the door open for a prolonged period
    while (openDoor) { QThread::msleep(1000); }

    alarm.setAlarm("OFF");
    door.close();

    //remove the reached floor
    destinations->removeFirst();

    //if the route has finished, inform the ecs
    if (destinations->isEmpty()) { emit elevatorStopped(id); }

    direction = 0;
}

//checks the distance from the elevator to the current floor
int Elevator::checkFloorDistance(int floor)
{
    if (sens.distance(eleLabel->pos(), floor) == 0) { return 0; }
    else { return sens.distance(eleLabel->pos(), floor) / 100; }
}
