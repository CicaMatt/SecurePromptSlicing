#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "your_username"
#define PASSWORD "your_password"
#define DATABASE "weather_data"

void temperature_for_location(double latitude, double longitude, const char *date);

int main() {
    // Example call
    temperature_for_location(34.0522, -118.2437, "2023-10-15");
    return 0;
}

void temperature_for_location(double latitude, double longitude, const char *date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM temperatures WHERE latitude = %f AND longitude = %f AND date = '%s'", latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res))) {
        printf("Temperature: %s°C\n", row[0]);
    } else {
        printf("No temperature data found for the specified location and date.\n");
    }

    mysql_free_result(res);
    mysql_close(conn);
}
