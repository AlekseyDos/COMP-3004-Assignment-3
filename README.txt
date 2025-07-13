Name: Aleksey Dosov

Student Number: 101221307


Launching and Building instructions:
The .pro file is located in the COMP3004Assignment3 folder.
Execute the COMP3004Assignment3.pro file and Qt creator will open with all components loaded.

If you want to launch the executable file outside Qt creator, navigate to the build-COMP3004Assignment3-Desktop-Debug folder.
Execute the COMP3004Assignment3 file and the program will launch outside of Qt creator.

Ensure that the build-COMP3004Assignment3-Desktop-Debug folder and the COMP3004Assignment3 folder are in the same directory just as presented in zip file.

Note: Running the program outside the Qt creator will remove access to the console output provided by QtDebug.
Most ECS information is printed to the console output.


Files and Folders:

COMP3004Assignment3Video.mp4
video demonstration of all scenarios in accordance with the sequence diagrams.

Note: In the video, the logic for the first success scenarios is slightly altered to correspond with the scenario only considering one elevator. When running in your instance where all elevators are considered, the ECS may call another elevator to service the floor due to that elevator being stationary. In both cases, the ECS acts appropriately when considering only one elevator or all elevators.

Assignment 3 (Aleksey Dosov).pdf
contains all the diagrams and descriptions for the entire system.

build-COMP3004Assignment3-Desktop-Debug Folder:
contains the Qt generated moc files that are used to generate the ui components and pair them with the back-end.

COMP3004Assignment3 File:
the executable program file that allows the program to run outside Qt creator.

COMP3004Assignment3 Folder:
contains the source code for the back end and the project file that can be loaded in Qt creator.

COMP3004Assignment3.pro:
project file that can be loaded in Qt creator.

main.cpp:
in charge of launching the ui and mainwindow.

mainwindow.cpp
contains all button handlers and ui components that need to be linked to the back-end.

mainwindow.h
header file for mainwindow.

mainwindow.ui
ui file for mainwindow.

elevatorcontrolsystem.cpp
contains all the decision-making for the elevator system.
controls and documents the movement of all the elevators.
ensures that all safety protocols and system-wide alarms are obeyed and followed.
responsible for communicating any pannel or floor requests to the elevators.

elevatorcontrolsystem.h
header file for elevatorcontrolsystem.

elevator.cpp
controls the movement of the elevator and its internal components.
listens to the ecs and performs tasks according to the information provided by the ecs.
responsible for properly displaying information to the passengers.

elevator.h
header file for elevator.

sensor.cpp
calculates and determines the elevators current position.
finds the position of the next floor relative to the elevator.
provides the direction the elevator needs to be traveling to reach the next floor.
calculates the distance between the elevator and the next floor.

sensor.h
header file for sensor.

door.cpp
controls the doors state.

door.h
header file for door.

display.cpp
controls the display state.

display.h
header file for display.

alarm.cpp
controls the alarm and audio states.

alarm.h
header file for alarm.

defs.h
defines the maximum number of elevators and maximum number of floors
