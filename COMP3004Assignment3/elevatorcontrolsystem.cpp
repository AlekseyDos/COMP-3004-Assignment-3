#include "elevatorcontrolsystem.h"

ElevatorControlSystem::ElevatorControlSystem()
{
    //connections used to communicate between the ecs and the elevators
    connect(this, &ElevatorControlSystem::moveElevator1, &ele1, &Elevator::moveElevator);
    connect(this, &ElevatorControlSystem::moveElevator2, &ele2, &Elevator::moveElevator);
    connect(this, &ElevatorControlSystem::moveElevator3, &ele3, &Elevator::moveElevator);

    //elevators are moved to new threads
    ele1.moveToThread(&_Ele1thread);
    ele2.moveToThread(&_Ele2thread);
    ele3.moveToThread(&_Ele3thread);

    _Ele1thread.start();
    _Ele2thread.start();
    _Ele3thread.start();

    //connections for the elevators to communicate back to the ecs
    connect(&ele1, &Elevator::elevatorStopped, this, &ElevatorControlSystem::elevatorStopped);
    connect(&ele2, &Elevator::elevatorStopped, this, &ElevatorControlSystem::elevatorStopped);
    connect(&ele3, &Elevator::elevatorStopped, this, &ElevatorControlSystem::elevatorStopped);

    //initial variable values
    ele1AlarmActive = false;
    ele2AlarmActive = false;
    ele3AlarmActive = false;

    safeFloor = 1;
}

//distribuets and assigns the Qt specific objects passed from the ui
void ElevatorControlSystem::assignElevatorLabels(QLabel *label1, QLabel *label2, QLabel *label3)
{
    ele1.assignElevatorLabel(label1);
    ele2.assignElevatorLabel(label2);
    ele3.assignElevatorLabel(label3);

    ele1.assignElevatorID(1);
    ele2.assignElevatorID(2);
    ele3.assignElevatorID(3);
}

void ElevatorControlSystem::setupUI(QLineEdit *ele1DS, QLineEdit *ele1MS, QLineEdit *ele1AL, QLineEdit *ele2DS, QLineEdit *ele2MS, QLineEdit *ele2AL, QLineEdit *ele3DS, QLineEdit *ele3MS, QLineEdit *ele3AL)
{
    ele1.setupUI(ele1DS, ele1MS, ele1AL);
    ele2.setupUI(ele2DS, ele2MS, ele2AL);
    ele3.setupUI(ele3DS, ele3MS, ele3AL);
}

//pannels communicate to the ecs which then dertermins where the elevator must go and documents its travel
void ElevatorControlSystem::pannelCall(int floor, int eleNum)
{
    switch (eleNum) {

    case 1:

        //checks if the selected elevator is in an alarm state
        if (ele1AlarmActive) {return;}

        //checks the direction the elevator needs to travel in
        if (ele1.getFloorDirection(floor) == 1)
        {
            //checks if the elevator is already planning to stop at the selected floor
            if (!(ele1DestinationsUp.contains(floor)))
            {
                //adds the floor to the elevators "up" route
                ele1DestinationsUp.append(floor);

                //sorts the elevator route
                std::sort(ele1DestinationsUp.begin(), ele1DestinationsUp.end());

                qDebug() << "Floor" << floor << "added on the way up for elevator 1:" << ele1DestinationsUp;

                //informs the elevator to move along its updated route
                emit moveElevator1(&ele1DestinationsUp);
            }
        }

        //checks the direction the elevator needs to travel in
        else if (ele1.getFloorDirection(floor) == 2)
        {
            //checks if the elevator is already planning to stop at the selected floor
            if (!(ele1DestinationsDown.contains(floor)))
            {
                //adds the floor to the elevators "down" route
                ele1DestinationsDown.append(floor);

                //sorts the elevator route
                std::sort(ele1DestinationsDown.rbegin(), ele1DestinationsDown.rend());

                qDebug() << "Floor" << floor << "added on the way down for elevator 1:" << ele1DestinationsDown;

                //informs the elevator to move along its updated route
                emit moveElevator1(&ele1DestinationsDown);
            }
        }

        break;

    case 2:

        //checks if the selected elevator is in an alarm state
        if (ele2AlarmActive) {return;}

        //checks the direction the elevator needs to travel in
        if (ele2.getFloorDirection(floor) == 1)
        {
            //checks if the elevator is already planning to stop at the selected floor
            if (!(ele2DestinationsUp.contains(floor)))
            {
                //adds the floor to the elevators "up" route
                ele2DestinationsUp.append(floor);

                //sorts the elevator route
                std::sort(ele2DestinationsUp.begin(), ele2DestinationsUp.end());

                qDebug() << "Floor" << floor << "added on the way up for elevator 2:" << ele2DestinationsUp;

                //informs the elevator to move along its updated route
                emit moveElevator2(&ele2DestinationsUp);
            }
        }

        //checks the direction the elevator needs to travel in
        else if (ele2.getFloorDirection(floor) == 2)
        {
            //checks if the elevator is already planning to stop at the selected floor
            if (!(ele2DestinationsDown.contains(floor)))
            {
                //adds the floor to the elevators "down" route
                ele2DestinationsDown.append(floor);

                //sorts the elevator route
                std::sort(ele2DestinationsDown.rbegin(), ele2DestinationsDown.rend());

                qDebug() << "Floor" << floor << "added on the way down for elevator 2:" << ele2DestinationsDown;

                //informs the elevator to move along its updated route
                emit moveElevator2(&ele2DestinationsDown);
            }
        }

        break;

    case 3:

        //checks if the selected elevator is in an alarm state
        if (ele3AlarmActive) {return;}

        //checks the direction the elevator needs to travel in
        if (ele3.getFloorDirection(floor) == 1)
        {
            //checks if the elevator is already planning to stop at the selected floor
            if (!(ele3DestinationsUp.contains(floor)))
            {
                //adds the floor to the elevators "up" route
                ele3DestinationsUp.append(floor);

                //sorts the elevator route
                std::sort(ele3DestinationsUp.begin(), ele3DestinationsUp.end());

                qDebug() << "Floor" << floor << "added on the way up for elevator 3:" << ele3DestinationsUp;

                //informs the elevator to move along its updated route
                emit moveElevator3(&ele3DestinationsUp);
            }
        }

        //checks the direction the elevator needs to travel in
        else if (ele3.getFloorDirection(floor) == 2)
        {
            //checks if the elevator is already planning to stop at the selected floor
            if (!(ele3DestinationsDown.contains(floor)))
            {
                //adds the floor to the elevators "down" route
                ele3DestinationsDown.append(floor);

                //sorts the elevator route
                std::sort(ele3DestinationsDown.rbegin(), ele3DestinationsDown.rend());

                qDebug() << "Floor" << floor << "added on the way down for elevator 3:" << ele3DestinationsDown;

                //informs the elevator to move along its updated route
                emit moveElevator3(&ele3DestinationsDown);
            }
        }

        break;

    default:
        break;
    }
}

//floor buttons communicate to the ecs which then dertermins where the elevator must go and documents its travel
void ElevatorControlSystem::floorCall(int floor, int direction)
{
    //variables
    int ele1Dis, ele2Dis, ele3Dis;

    ele1Dis = ele1.checkFloorDistance(floor);
    ele2Dis = ele2.checkFloorDistance(floor);
    ele3Dis = ele3.checkFloorDistance(floor);

    //if the elevators are stationary, select those elevators starting with the left most elevator
    if (ele1.getDirection() == 0 && !ele1AlarmActive)
    {
        qDebug() << "Selected Best Elevator: 1";
        pannelCall(floor, 1);
    }

    else if (ele2.getDirection() == 0 && !ele2AlarmActive)
    {
        qDebug() << "Selected Best Elevator: 2";
        pannelCall(floor, 2);
    }

    else if (ele3.getDirection() == 0 && !ele3AlarmActive)
    {
        qDebug() << "Selected Best Elevator: 3";
        pannelCall(floor, 3);
    }

    //if the elevators are on the same floor as the called floor, select those elevators starting with the left most elevator
    else if (ele1Dis == 0 && !ele1AlarmActive)
    {
        qDebug() << "Selected Best Elevator: 1";

        //checks which direction the elevator is traveling in
        if (ele1.getDirection() != 2) { ele1DestinationsUp.insert(0, floor); }
        else { ele1DestinationsDown.insert(0, floor); }
    }

    else if (ele2Dis == 0 && !ele2AlarmActive)
    {
        qDebug() << "Selected Best Elevator: 2";

        //checks which direction the elevator is traveling in
        if (ele2.getDirection() != 2) { ele2DestinationsUp.insert(0, floor); }
        else { ele2DestinationsDown.insert(0, floor); }
    }

    else if (ele3Dis == 0 && !ele3AlarmActive)
    {
        qDebug() << "Selected Best Elevator: 3";

        //checks which direction the elevator is traveling in
        if (ele3.getDirection() != 2) { ele3DestinationsUp.insert(0, floor); }
        else { ele3DestinationsDown.insert(0, floor); }
    }

    //if the elevators are at the same distance from the called floor, select those elevators starting with the left most elevator
    else if (std::abs(ele1Dis) == std::abs(ele2Dis) && std::abs(ele1Dis) == std::abs(ele3Dis))
    {
        //select the elevator that is moving in the direction of the called floor
        if (ele1.getDirection() == direction && !ele1AlarmActive)
        {
            qDebug() << "Selected Best Elevator: 1";
            pannelCall(floor, 1);
        }

        else if (ele2.getDirection() == direction && !ele2AlarmActive)
        {
            qDebug() << "Selected Best Elevator: 2";
            pannelCall(floor, 2);
        }

        else if (ele3.getDirection() == direction && !ele3AlarmActive)
        {
            qDebug() << "Selected Best Elevator: 3";
            pannelCall(floor, 3);
        }
    }

    //if the elevators are at different distances, select the closest elevators starting with the left most elevator
    else if (std::abs(ele1Dis) < std::abs(ele2Dis) && std::abs(ele1Dis) < std::abs(ele3Dis) && !ele1AlarmActive)
    {
        //select the elevator that is moving in the direction of the called floor
        if (ele1.getDirection() == direction)
        {
            qDebug() << "Selected Best Elevator: 1";
            pannelCall(floor, 1);
        }
    }

    else if (std::abs(ele2Dis) < std::abs(ele3Dis) && !ele2AlarmActive)
    {
        if (ele2.getDirection() == direction)
        {
            qDebug() << "Selected Best Elevator: 2";
            pannelCall(floor, 2);
        }
    }

    else if (ele3.getDirection() == direction && !ele3AlarmActive)
    {
        qDebug() << "Selected Best Elevator: 3";
        pannelCall(floor, 3);
    }

    //if all elevators are equally ineligible, select the left most elevator
    else if (!ele1AlarmActive)
    {
        qDebug() << "Selected Best Elevator: 1";
        pannelCall(floor, 1);
    }

}

//if the elevator finishes its "up" or "down" route, check if the opposite route is not empty and move the elevator
void ElevatorControlSystem::elevatorStopped(int id)
{
    switch (id) {

    case 1:

        //check both routes to see if there are any floors that are queued
        if (!(ele1DestinationsUp.isEmpty())) { emit moveElevator1(&ele1DestinationsUp); }

        else if (!(ele1DestinationsDown.isEmpty())) { emit moveElevator1(&ele1DestinationsDown); }

        break;

    case 2:

        //check both routes to see if there are any floors that are queued
        if (!(ele2DestinationsUp.isEmpty())) { emit moveElevator2(&ele2DestinationsUp); }

        else if (!(ele2DestinationsDown.isEmpty())) { emit moveElevator2(&ele2DestinationsDown); }

        break;

    case 3:

        //check both routes to see if there are any floors that are queued
        if (!(ele3DestinationsUp.isEmpty())) { emit moveElevator3(&ele3DestinationsUp); }

        else if (!(ele3DestinationsDown.isEmpty())) { emit moveElevator3(&ele3DestinationsDown); }

        break;
    }
}

//communicates to the evelator when the "close door" button is pressed
void ElevatorControlSystem::closeDoorButton(int eleNum, bool checked)
{
    switch (eleNum) {

    case 1:
        ele1.setDoorButtonState(1, checked);
        break;

    case 2:
        ele2.setDoorButtonState(1, checked);
        break;

    case 3:
        ele3.setDoorButtonState(1, checked);
        break;

    default:
        break;
    }
}

//communicates to the evelator when the "open door" button is pressed
void ElevatorControlSystem::openDoorButton(int eleNum, bool checked)
{
    switch (eleNum) {

    case 1:
        ele1.setDoorButtonState(2, checked);
        break;

    case 2:
        ele2.setDoorButtonState(2, checked);
        break;

    case 3:
        ele3.setDoorButtonState(2, checked);
        break;

    default:
        break;
    }
}

//communicates to the evelator when the "help alarm" button is pressed
void ElevatorControlSystem::helpAlarm(int eleNum, bool checked)
{
    switch (eleNum) {

    case 1:

        //sets the elevator alarm state
        ele1AlarmActive = checked;
        if (checked)
        {

            //clears the routes
            ele1DestinationsUp.clear();
            ele1DestinationsDown.clear();

            //updates the routes with the safe floor destination
            ele1DestinationsUp.insert(0, safeFloor);
            ele1DestinationsDown.insert(0, safeFloor);

            //update the alarms and calls the elevator to move
            ele1.setAlarm("HELP");

            qDebug() << "Connecting Elevator 1 With Operators";

            emit moveElevator1(&ele1DestinationsDown);
        }
        break;

    case 2:

        //sets the elevator alarm state
        ele2AlarmActive = checked;
        if (checked)
        {
            //clears the routes
            ele2DestinationsUp.clear();
            ele2DestinationsDown.clear();

            //updates the routes with the safe floor destination
            ele2DestinationsUp.insert(0, safeFloor);
            ele2DestinationsDown.insert(0, safeFloor);

            //update the alarms and calls the elevator to move
            ele2.setAlarm("HELP");

            qDebug() << "Connecting Elevator 2 With Operators";

            emit moveElevator2(&ele2DestinationsDown);
        }
        break;

    case 3:

        //sets the elevator alarm state
        ele3AlarmActive = checked;
        if (checked)
        {

            //clears the routes
            ele3DestinationsUp.clear();
            ele3DestinationsDown.clear();

            //updates the routes with the safe floor destination
            ele3DestinationsUp.insert(0, safeFloor);
            ele3DestinationsDown.insert(0, safeFloor);

            //update the alarms and calls the elevator to move
            ele3.setAlarm("HELP");

            qDebug() << "Connecting Elevator 3 With Operators";

            emit moveElevator3(&ele3DestinationsDown);
        }
        break;

    default:
        break;
    }
}

//communicates to the elevators if there is a building wide alarm
void ElevatorControlSystem::alarms(QString text, bool checked)
{
    //sets the elevator alarm state
    ele1AlarmActive = checked;
    ele2AlarmActive = checked;
    ele3AlarmActive = checked;

    if (checked)
    {

        //clears the routes
        ele1DestinationsUp.clear();
        ele1DestinationsDown.clear();

        ele2DestinationsUp.clear();
        ele2DestinationsDown.clear();

        ele3DestinationsUp.clear();
        ele3DestinationsDown.clear();

        //updates the routes with the safe floor destination
        ele1DestinationsUp.insert(0, safeFloor);
        ele1DestinationsDown.insert(0, safeFloor);

        ele2DestinationsUp.insert(0, safeFloor);
        ele2DestinationsDown.insert(0, safeFloor);

        ele3DestinationsUp.insert(0, safeFloor);
        ele3DestinationsDown.insert(0, safeFloor);

        //update the alarms and calls the elevator to move
        ele1.setAlarm(text);
        ele2.setAlarm(text);
        ele3.setAlarm(text);

        qDebug() << "BUILDING WIDE" << text;

        emit moveElevator1(&ele1DestinationsDown);
        emit moveElevator2(&ele2DestinationsDown);
        emit moveElevator3(&ele3DestinationsDown);
    }
}

//sets the elevators overload state
void ElevatorControlSystem::overload(int eleNum, bool checked)
{
    switch (eleNum) {

    case 1:
        ele1.setOverload(checked);
        break;

    case 2:
        ele2.setOverload(checked);
        break;

    case 3:
        ele3.setOverload(checked);
        break;

    default:
        break;
    }

}

//sets the elevators obstical state
void ElevatorControlSystem::obstical(int eleNum, bool checked)
{
    switch (eleNum) {

    case 1:
        ele1.setObstical(checked);
        break;

    case 2:
        ele2.setObstical(checked);
        break;

    case 3:
        ele3.setObstical(checked);
        break;

    default:
        break;
    }
}
