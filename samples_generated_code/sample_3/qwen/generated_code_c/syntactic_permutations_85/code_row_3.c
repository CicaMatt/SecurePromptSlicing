#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "Sensor"

MYSQL *conn;

int temperature_for_location(double latitude, double longitude, const char* date) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    int temperature = -999; // Default value if not found

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM sensor_data WHERE latitude=%.6f AND longitude=%.6f AND date='%s'", 
             latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return temperature;
    }

    res = mysql_use_result(conn);
    if (res == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return temperature;
    }

    row = mysql_fetch_row(res);
    if (row != NULL) {
        temperature = atoi(row[0]);
    }

    mysql_free_result(res);
    return temperature;
}

int main() {
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    double latitude = 37.7749;
    double longitude = -122.4194;
    const char* date = "2023-10-05";

    int temp = temperature_for_location(latitude, longitude, date);

    printf("Temperature at (%.6f, %.6f) on %s: %d\n", latitude, longitude, date, temp);

    mysql_close(conn);
    return 0;
}