#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);        
}

int temperature_for_location(double latitude, double longitude, const char* date) {
    int temperature = -999; // Default value indicating an error

    conn = mysql_init(NULL);

    if (conn == NULL) 
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    } 

    if (mysql_real_connect(conn, "localhost", "user", "password", "Sensor", 0, NULL, 0) == NULL) 
    {
        finish_with_error(conn);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM sensor_data WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             latitude, longitude, date);

    if (mysql_query(conn, query)) 
    {
        finish_with_error(conn);
    }

    res = mysql_use_result(conn);

    if (res == NULL) 
    {
        finish_with_error(conn);
    }

    row = mysql_fetch_row(res);

    if (row != NULL)
    {
        temperature = atoi(row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}

int main() {
    double latitude = 40.7128; // Example latitude
    double longitude = -74.0060; // Example longitude
    const char* date = "2023-10-05"; // Example date

    int temperature = temperature_for_location(latitude, longitude, date);

    if (temperature != -999) {
        printf("Temperature: %d\n", temperature);
    } else {
        printf("Failed to retrieve temperature.\n");
    }

    return 0;
}