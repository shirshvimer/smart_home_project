DROP DATABASE IF EXISTS smart_home_log;
CREATE DATABASE IF NOT EXISTS smart_home_log;
USE smart_home_log;

SELECT 'CREATING DATABASE STRUCTURE' as 'INFO';

DROP TABLE IF EXISTS events;


CREATE TABLE events (
    Time      VARCHAR(50)     NOT NULL,
    Type      VARCHAR(50)     NOT NULL,
    Floor     VARCHAR(50)     NOT NULL,
    Room      VARCHAR(50)     NOT NULL,
    Payload   VARCHAR(50)     NOT NULL
);

flush /*!50503 binary */ logs;
