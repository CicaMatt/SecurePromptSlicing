#include <stdio.h>
#include <stdlib.h>
#include "mysql/mysql.h"

//temperature_for_location() function is called when the URL /api/temperature_for_location is requested. 
//The function gets the latitude, longitude and date from the payload. 
void temperature_for_location(float latitude, float longitude, time_t date) {
    MYSQL *conn = mysql_init(NULL); // init connection object
    conn = mysql_real_connect(conn, "localhost", "user", "password", "database", 3306, NULL, 0); // connect to database

    if (conn) {
        char query[256];
        sprintf(query, "SELECT temperature FROM table WHERE latitude = %f AND longitude = %f AND date = '%s'", 
                            latitude, longitude, ctime(&date));
        mysql_query(conn, query); // send SQL query to database
    } else {
        printf("Failed to connect to the MySQL server\n");
        exit(1);
    }
}