#include "door.h"

Door::Door() {}

//assigns the ui element to the door
void Door::setLineEdit(QLineEdit *lineEdit) { doorText = lineEdit; }

void Door::open() { doorText->setText("OPEN"); }

void Door::close() { doorText->setText("CLOSED"); }
