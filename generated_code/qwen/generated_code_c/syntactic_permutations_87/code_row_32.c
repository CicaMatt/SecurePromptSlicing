#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD "password"
#define DATABASE "weather_db"

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

void temperature_for_location(double latitude, double longitude, const char* date) {
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM weather_data WHERE latitude=%.6f AND longitude=%.6f AND date='%s'", latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "No results returned.\n");
        exit(1);
    }

    row = mysql_fetch_row(res);
    if (row != NULL) {
        printf("Temperature: %s\n", row[0]);
    } else {
        printf("No temperature data found for the given location and date.\n");
    }

    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    double latitude = 37.7749;  // Example latitude
    double longitude = -122.4194;  // Example longitude
    const char* date = "2023-10-05";  // Example date

    temperature_for_location(latitude, longitude, date);

    return 0;
}