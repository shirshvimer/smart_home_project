# h71.prj.room7

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
