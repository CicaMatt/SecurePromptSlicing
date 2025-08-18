#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "weather_db"

double temperature_for_location(double latitude, double longitude, const char* date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query),
             "SELECT temperature FROM temperatures WHERE latitude = %f AND longitude = %f AND date = '%s'",
             latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_store_result(conn);
    if (!res) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    row = mysql_fetch_row(res);
    double temperature = 0.0;
    if (row && row[0]) {
        temperature = atof(row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}

int main() {
    // Example usage
    double latitude = 37.7749;
    double longitude = -122.4194;
    const char* date = "2023-10-01";

    double temp = temperature_for_location(latitude, longitude, date);
    printf("Temperature: %f\n", temp);

    return 0;
}