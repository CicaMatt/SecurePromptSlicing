#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "Sensor"

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

int get_temperature_for_location(double latitude, double longitude, char* date) {
    int temperature = -1;
    char query[256];

    snprintf(query, sizeof(query), "SELECT temperature FROM sensor_data WHERE latitude=%.6f AND longitude=%.6f AND date='%s'", latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res))) {
        temperature = atoi(row[0]);
    }

    mysql_free_result(res);
    return temperature;
}

void temperature_for_location(double latitude, double longitude, char* date) {
    int temperature = get_temperature_for_location(latitude, longitude, date);

    if (temperature != -1) {
        printf("Temperature: %d\n", temperature);
    } else {
        printf("Failed to retrieve temperature.\n");
    }
}

int main() {
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    double latitude = 40.7128;
    double longitude = -74.0060;
    char date[] = "2023-10-05";

    temperature_for_location(latitude, longitude, date);

    mysql_close(conn);

    return 0;
}