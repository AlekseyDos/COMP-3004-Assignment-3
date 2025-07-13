#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "elevatorcontrolsystem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_elevator1_button1_clicked();
    void on_elevator1_button2_clicked();
    void on_elevator1_button3_clicked();
    void on_elevator1_button4_clicked();
    void on_elevator1_button6_clicked();
    void on_elevator1_button5_clicked();
    void on_elevator1_button7_clicked();

    void on_elevator2_button1_clicked();
    void on_elevator2_button2_clicked();
    void on_elevator2_button3_clicked();
    void on_elevator2_button4_clicked();
    void on_elevator2_button5_clicked();
    void on_elevator2_button6_clicked();
    void on_elevator2_button7_clicked();

    void on_elevator3_button1_clicked();
    void on_elevator3_button2_clicked();
    void on_elevator3_button3_clicked();
    void on_elevator3_button4_clicked();
    void on_elevator3_button5_clicked();
    void on_elevator3_button6_clicked();
    void on_elevator3_button7_clicked();

    void on_floor1_buttonup_clicked();
    void on_floor2_buttonup_clicked();
    void on_floor3_buttonup_clicked();
    void on_floor4_buttonup_clicked();
    void on_floor5_buttonup_clicked();
    void on_floor6_buttonup_clicked();

    void on_floor2_buttondown_clicked();
    void on_floor3_buttondown_clicked();
    void on_floor4_buttondown_clicked();
    void on_floor5_buttondown_clicked();
    void on_floor6_buttondown_clicked();
    void on_floor7_buttondown_clicked();

    void on_elevator1_buttonclose_pressed();
    void on_elevator2_buttonclose_pressed();
    void on_elevator3_buttonclose_pressed();

    void on_elevator1_buttonopen_pressed();
    void on_elevator2_buttonopen_pressed();
    void on_elevator3_buttonopen_pressed();

    void on_elevator1_buttonclose_released();
    void on_elevator2_buttonclose_released();
    void on_elevator3_buttonclose_released();

    void on_elevator1_buttonopen_released();
    void on_elevator2_buttonopen_released();
    void on_elevator3_buttonopen_released();

    void on_elevator1_buttonhelp_toggled(bool checked);
    void on_elevator2_buttonhelp_toggled(bool checked);
    void on_elevator3_buttonhelp_toggled(bool checked);

    void on_button_poweroutage_toggled(bool checked);
    void on_button_firealarm_toggled(bool checked);

    void on_elevator1_buttonoverload_toggled(bool checked);
    void on_elevator2_buttonoverload_toggled(bool checked);
    void on_elevator3_buttonoverload_toggled(bool checked);

    void on_elevator1_buttonobstacle_toggled(bool checked);
    void on_elevator2_buttonobstacle_toggled(bool checked);
    void on_elevator3_buttonobstacle_toggled(bool checked);

signals:
    void floorCall(int floor, int direction);
    void pannelCall(int floor, int eleNum);
    void closeDoorButton(int eleNum, bool checked);
    void openDoorButton(int eleNum, bool checked);
    void helpAlarm(int eleNum, bool checked);
    void alarms(QString text, bool checked);
    void overload(int eleNum, bool checked);
    void obstical(int eleNum, bool checked);

private:
    Ui::MainWindow *ui;
    ElevatorControlSystem ecs;
    QThread _ECSthread;

};
#endif // MAINWINDOW_H
