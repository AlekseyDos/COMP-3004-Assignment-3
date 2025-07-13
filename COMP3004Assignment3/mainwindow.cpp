#include "mainwindow.h"
#include "ui_mainwindow.h"

//sets up the gui and the ecs
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //set up functions that pass along Qt specific objects
    ecs.assignElevatorLabels(ui->elevator1, ui->elevator2, ui->elevator3);
    ecs.setupUI(ui->elevator1_dsline, ui->elevator1_msgline, ui->elevator1_alrline, ui->elevator2_dsline, ui->elevator2_msgline, ui->elevator2_alrline, ui->elevator3_dsline, ui->elevator3_msgline, ui->elevator3_alrline);

    //connections between the signals and slots used to communicate between Main window and the ecs
    connect(this, &MainWindow::floorCall, &ecs, &ElevatorControlSystem::floorCall);
    connect(this, &MainWindow::pannelCall, &ecs, &ElevatorControlSystem::pannelCall);

    connect(this, &MainWindow::closeDoorButton, &ecs, &ElevatorControlSystem::closeDoorButton);
    connect(this, &MainWindow::openDoorButton, &ecs, &ElevatorControlSystem::openDoorButton);

    connect(this, &MainWindow::helpAlarm, &ecs, &ElevatorControlSystem::helpAlarm);
    connect(this, &MainWindow::alarms, &ecs, &ElevatorControlSystem::alarms);

    connect(this, &MainWindow::overload, &ecs, &ElevatorControlSystem::overload);
    connect(this, &MainWindow::obstical, &ecs, &ElevatorControlSystem::obstical);

    //moves the ecs to a new thread
    ecs.moveToThread(&_ECSthread);

    _ECSthread.start();
}

MainWindow::~MainWindow()
{
    _ECSthread.quit();
    delete ui;
}

//all button handlers for the ui
void MainWindow::on_elevator1_button1_clicked() { emit pannelCall(1, 1); }
void MainWindow::on_elevator1_button2_clicked() { emit pannelCall(2, 1); }
void MainWindow::on_elevator1_button3_clicked() { emit pannelCall(3, 1); }
void MainWindow::on_elevator1_button4_clicked() { emit pannelCall(4, 1); }
void MainWindow::on_elevator1_button5_clicked() { emit pannelCall(5, 1); }
void MainWindow::on_elevator1_button6_clicked() { emit pannelCall(6, 1); }
void MainWindow::on_elevator1_button7_clicked() { emit pannelCall(7, 1); }

void MainWindow::on_elevator2_button1_clicked() { emit pannelCall(1, 2); }
void MainWindow::on_elevator2_button2_clicked() { emit pannelCall(2, 2); }
void MainWindow::on_elevator2_button3_clicked() { emit pannelCall(3, 2); }
void MainWindow::on_elevator2_button4_clicked() { emit pannelCall(4, 2); }
void MainWindow::on_elevator2_button5_clicked() { emit pannelCall(5, 2); }
void MainWindow::on_elevator2_button6_clicked() { emit pannelCall(6, 2); }
void MainWindow::on_elevator2_button7_clicked() { emit pannelCall(7, 2); }

void MainWindow::on_elevator3_button1_clicked() { emit pannelCall(1, 3); }
void MainWindow::on_elevator3_button2_clicked() { emit pannelCall(2, 3); }
void MainWindow::on_elevator3_button3_clicked() { emit pannelCall(3, 3); }
void MainWindow::on_elevator3_button4_clicked() { emit pannelCall(4, 3); }
void MainWindow::on_elevator3_button5_clicked() { emit pannelCall(5, 3); }
void MainWindow::on_elevator3_button6_clicked() { emit pannelCall(6, 3); }
void MainWindow::on_elevator3_button7_clicked() { emit pannelCall(7, 3); }

//with accordance to the sensor class, 1 represents up and 2 represents down
void MainWindow::on_floor1_buttonup_clicked() { emit floorCall(1, 1); }
void MainWindow::on_floor2_buttonup_clicked() { emit floorCall(2, 1); }
void MainWindow::on_floor3_buttonup_clicked() { emit floorCall(3, 1); }
void MainWindow::on_floor4_buttonup_clicked() { emit floorCall(4, 1); }
void MainWindow::on_floor5_buttonup_clicked() { emit floorCall(5, 1); }
void MainWindow::on_floor6_buttonup_clicked() { emit floorCall(6, 1); }

void MainWindow::on_floor2_buttondown_clicked() { emit floorCall(2, 2); }
void MainWindow::on_floor3_buttondown_clicked() { emit floorCall(3, 2); }
void MainWindow::on_floor4_buttondown_clicked() { emit floorCall(4, 2); }
void MainWindow::on_floor5_buttondown_clicked() { emit floorCall(5, 2); }
void MainWindow::on_floor6_buttondown_clicked() { emit floorCall(6, 2); }
void MainWindow::on_floor7_buttondown_clicked() { emit floorCall(7, 2); }

void MainWindow::on_elevator1_buttonclose_pressed() { emit closeDoorButton(1, true); }
void MainWindow::on_elevator2_buttonclose_pressed() { emit closeDoorButton(2, true); }
void MainWindow::on_elevator3_buttonclose_pressed() { emit closeDoorButton(3, true); }

void MainWindow::on_elevator1_buttonopen_pressed() { emit openDoorButton(1, true); }
void MainWindow::on_elevator2_buttonopen_pressed() { emit openDoorButton(2, true); }
void MainWindow::on_elevator3_buttonopen_pressed() { emit openDoorButton(3, true); }

void MainWindow::on_elevator1_buttonclose_released() { emit closeDoorButton(1, false); }
void MainWindow::on_elevator2_buttonclose_released() { emit closeDoorButton(2, false); }
void MainWindow::on_elevator3_buttonclose_released() { emit closeDoorButton(3, false); }

void MainWindow::on_elevator1_buttonopen_released() { emit openDoorButton(1, false); }
void MainWindow::on_elevator2_buttonopen_released() { emit openDoorButton(2, false); }
void MainWindow::on_elevator3_buttonopen_released() { emit openDoorButton(3, false); }

void MainWindow::on_elevator1_buttonhelp_toggled(bool checked) { emit helpAlarm(1, checked); }
void MainWindow::on_elevator2_buttonhelp_toggled(bool checked) { emit helpAlarm(2, checked); }
void MainWindow::on_elevator3_buttonhelp_toggled(bool checked) { emit helpAlarm(3, checked); }

void MainWindow::on_button_poweroutage_toggled(bool checked) { emit alarms("POWER OUT", checked); }
void MainWindow::on_button_firealarm_toggled(bool checked) { emit alarms("FIRE", checked); }

void MainWindow::on_elevator1_buttonoverload_toggled(bool checked) { emit overload(1, checked); }
void MainWindow::on_elevator2_buttonoverload_toggled(bool checked) { emit overload(2, checked); }
void MainWindow::on_elevator3_buttonoverload_toggled(bool checked) { emit overload(3, checked); }

void MainWindow::on_elevator1_buttonobstacle_toggled(bool checked) { emit obstical(1, checked); }
void MainWindow::on_elevator2_buttonobstacle_toggled(bool checked) { emit obstical(2, checked); }
void MainWindow::on_elevator3_buttonobstacle_toggled(bool checked) { emit obstical(3, checked); }



