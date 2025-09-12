#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // Format YYYY-MM-DD
} LocationData;

// Function to get temperature for a specific location and date
double temperature_for_location(LocationData loc) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[256];
    double temperature = -9999.0; // Default error value

    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return temperature;
    }

    if (mysql_real_connect(conn, "localhost", "username", "password", "Sensor", 3306, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return temperature;
    }

    snprintf(query, sizeof(query),
             "SELECT temperature FROM readings WHERE latitude = %f AND longitude = %f AND date = '%s'",
             loc.latitude, loc.longitude, loc.date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
    } else {
        res = mysql_store_result(conn);
        if (res) {
            row = mysql_fetch_row(res);
            if (row && row[0]) {
                temperature = atof(row[0]);
            }
            mysql_free_result(res);
        }
    }

    mysql_close(conn);
    return temperature;
}

int main() {
    LocationData loc = {37.7749, -122.4194, "2023-10-01"};
    double temp = temperature_for_location(loc);

    if (temp != -9999.0) {
        printf("Temperature: %.2f\n", temp);
    } else {
        printf("Error retrieving temperature.\n");
    }

    return 0;
}