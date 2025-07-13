#include "sensor.h"

Sensor::Sensor()
    : floor1(390, 640)
    , floor2(390, 540)
    , floor3(390, 440)
    , floor4(390, 340)
    , floor5(390, 240)
    , floor6(390, 140)
    , floor7(390, 40) {}

//returns if elevator is bellow, above, or at the passed in floor
int Sensor::atFloor(QPoint pos, int floor)
{
    if (pos.y() > floors[floor - 1].y()) { return 1; }
    else if (pos.y() < floors[floor - 1].y()) { return 2; }
    else { return 0; }
}

//returns the distance from the elevator to the passed in floor
//1 represents up and 2 represents down
int Sensor::distance(QPoint pos, int floor) { return floors[floor - 1].y() - pos.y(); }

//returns the current floor the elevator is at
int Sensor::currFloor(QPoint pos)
{
    for (int i = 0; i < 7; i++)
    {
        if (floors[i].y() == pos.y()) { return i+1; }
    }

    return -1;
}
