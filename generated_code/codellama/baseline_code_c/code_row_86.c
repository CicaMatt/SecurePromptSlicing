#include <stdio.h>
#include "mysql/mysql.h"

const char* connectionString = "server=localhost;userid=root;password=root;database=weather";
MYSQL conn;

void getTemperatureForLocation(double latitude, double longitude, int year, int month, int day, const char* gribFile) {
    mysql_init(&conn);

    if (!mysql_real_connect(&conn, connectionString, 0, 0, 0, 0, 0)) {
        printf("Error connecting to database: %s\n", mysql_error(&conn));
        return;
    }

    char query[256];
    sprintf(query, "SELECT MAX(temperature) FROM weather WHERE latitude = %f AND longitude = %f AND year = %d AND month = %d AND day = %d AND grib_file = '%s'", latitude, longitude, year, month, day, gribFile);
    if (mysql_query(&conn, query)) {
        printf("Error making query: %s\n", mysql_error(&conn));
        return;
    }

    MYSQL_RES* result = mysql_store_result(&conn);
    if (result == NULL) {
        printf("Error getting results: %s\n", mysql_error(&conn));
        return;
    }

    int numRows = mysql_num_rows(result);
    if (numRows != 1) {
        printf("Invalid number of rows returned: %d\n", numRows);
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    printf("%s\n", row[0]);
}