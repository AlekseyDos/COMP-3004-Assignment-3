#include "display.h"

Display::Display() {}

//assigns the ui element to the display
void Display::setLineEdit(QLineEdit *lineEdit) { displayText = lineEdit; }

void Display::displayMessage(QString text) { displayText->setText(text); }
