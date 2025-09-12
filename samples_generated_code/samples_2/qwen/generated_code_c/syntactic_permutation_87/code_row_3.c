#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "user"
#define PASS "password"
#define DB "weather_db"

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

int get_temperature_for_location(double latitude, double longitude, const char* date) {
    int temperature = -1;
    char query[256];

    snprintf(query, sizeof(query), "SELECT temperature FROM weather_data WHERE latitude=%.6f AND longitude=%.6f AND date='%s'", latitude, longitude, date);

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
    if (row != NULL && row[0] != NULL) {
        temperature = atoi(row[0]);
    }

    mysql_free_result(res);
    return temperature;
}

void temperature_for_location(double latitude, double longitude, const char* date) {
    conn = mysql_init(NULL);

    if (mysql_real_connect(conn, HOST, USER, PASS, DB, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    int temperature = get_temperature_for_location(latitude, longitude, date);
    printf("Temperature: %d\n", temperature);

    mysql_close(conn);
}

int main() {
    double latitude = 37.7749;
    double longitude = -122.4194;
    const char* date = "2023-10-01";

    temperature_for_location(latitude, longitude, date);

    return 0;
}