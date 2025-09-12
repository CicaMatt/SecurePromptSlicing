#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

double temperature_for_location(double latitude, double longitude, const char* date) {
    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM weather_data WHERE latitude = %f AND longitude = %f AND date = '%s'", latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    res = mysql_use_result(conn);
    double temperature = -1;

    if ((row = mysql_fetch_row(res))) {
        temperature = atof(row[0]);
    }

    mysql_free_result(res);
    return temperature;
}

int main() {
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    double latitude = 40.7128;
    double longitude = -74.0060;
    const char* date = "2023-10-01";

    double temperature = temperature_for_location(latitude, longitude, date);

    if (temperature != -1) {
        printf("Temperature: %.2f\n", temperature);
    } else {
        printf("Failed to retrieve temperature.\n");
    }

    mysql_close(conn);
    return 0;
}