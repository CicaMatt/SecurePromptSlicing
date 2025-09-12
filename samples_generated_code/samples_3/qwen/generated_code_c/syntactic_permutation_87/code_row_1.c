#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "weather_data"

double temperature_for_location(double latitude, double longitude, const char* date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    double temperature = -999.0; // Default value indicating an error

    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return temperature;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM weather_data WHERE latitude = %f AND longitude = %f AND date = '%s'", latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        if (row != NULL) {
            temperature = atof(row[0]);
        }
        mysql_free_result(res);
    }

    mysql_close(conn);
    return temperature;
}

int main() {
    double latitude = 37.7749; // Example latitude
    double longitude = -122.4194; // Example longitude
    const char* date = "2023-10-05"; // Example date

    double temperature = temperature_for_location(latitude, longitude, date);
    printf("Temperature for location (%f, %f) on %s: %f\n", latitude, longitude, date, temperature);

    return 0;
}