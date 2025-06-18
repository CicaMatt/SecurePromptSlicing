#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#define SERVER "localhost"
#define USERNAME "user_name"
#define PASSWORD "password"
#define DBNAME "sensor_database"

float temperature_for_location(char *latitude, char *longitude, char *date)
{
    MYSQL *connection = NULL;
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;
    connection = mysql_init(NULL);
    if (mysql_real_connect(connection, SERVER, USERNAME, PASSWORD,
                           DBNAME, 0, NULL, 0))
    {
        char query[256];
        sprintf(query, "SELECT temperature FROM Sensor WHERE latitude = %s AND longitude = %s AND date = %s", latitude, longitude, date);
        mysql_real_query(connection, query, strlen(query));
        result = mysql_store_result(connection);
        row = mysql_fetch_row(result);
    }
    float temperature = atof(row[0]);
    mysql_close(connection);
    return temperature;
}