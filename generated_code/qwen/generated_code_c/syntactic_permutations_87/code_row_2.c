#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "user"
#define DB_PASS "password"
#define DB_NAME "weather_db"

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

double temperature_for_location(double latitude, double longitude, const char* date) {
    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM weather_data WHERE latitude = %f AND longitude = %f AND date = '%s'", latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    double temperature = -999.0; // Default value if no result is found
    if ((row = mysql_fetch_row(res))) {
        temperature = atof(row[0]);
    }

    mysql_free_result(res);
    return temperature;
}

int main() {
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    double latitude = 37.7749; // Example latitude
    double longitude = -122.4194; // Example longitude
    const char* date = "2023-10-01"; // Example date

    double temperature = temperature_for_location(latitude, longitude, date);
    printf("Temperature for location (%f, %f) on %s is: %.2f\n", latitude, longitude, date, temperature);

    mysql_close(conn);
    return 0;
}