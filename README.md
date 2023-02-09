# SMART HOME

## Summary

SmartHome is a next generation platform for managing IoT enhanced smart buildings. The platform serves as the controller and integration hub for modules, devices, controllers and sensors that will enable efficient and comfortable operation of the building.
SmartHome is implemented using C++.

## Main Components

The system includes the following components:

A central hub, which is a server application serving as a host for software agents (below). It provides an efficient mechanism to receive events from sensors and dispatch these events to relevant controllers.

Software agents, mediating communication with the external hardware devices. These devices can act either as sensors- monitoring and measuring a physical phenomena- or as controllers- executing an operation, usually affecting the environment.

Sensor agents generate events which will be routed to the controller agents interested in acting upon them. Generated events contain at least: the event type, the event location, a timestamp and a data payload. See design/diagrams/ for a detailed overview of the system's flow.

Agents are loaded at system startup according to a configuration file (.ini). Each agent shall be implemented as a dynamic object (.so).

## How To Run The Project

1.  Main flow:

    1.1) In folder: tests/main/server

        ---> LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../../../library/
        ---> export LD_LIBRARY_PATH
        ---> Run the server by "make check".

    1.2) In folder: tests/main/client

        ---> Run the client by "make check".

    After that, a file named "log.txt" will be created and all events will be saved in it.

2.  Main flow (saving the events to database)

    2.1) Open database with mysql:

        ---> In the console window start mysql with your user.
        ---> Run the following command (make sure the path is correct):
        source /home/user/Smart_home/sql/log.sql

    2.2) In folder: tests/main/server_with_db

        ---> In file "main_server_db.cpp" update the username and password
        in line 21 to your username and password in mysql.
        Write in console:
        ---> LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../../../library/
        ---> export LD_LIBRARY_PATH
        ---> Run the server by "make check".

    2.3) In file: tests/main/client

        ---> Run the client by "make check".

3.  Unitest with one event:
    In folder: tests/test_sensor_temp/

        ---> LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../../library/
        ---> export LD_LIBRARY_PATH
        ---> "make check"
