#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "user"
#define PASSWORD "password"
#define DATABASE "weather_db"

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

int get_temperature_for_location(double latitude, double longitude, const char* date) {
    int temperature = -999; // Default to an invalid value
    char query[256];

    snprintf(query, sizeof(query), "SELECT temperature FROM weather_data WHERE latitude = %.6f AND longitude = %.6f AND date = '%s'", latitude, longitude, date);

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

int main(int argc, char* argv[]) {
    double latitude = 37.7749; // Example latitude
    double longitude = -122.4194; // Example longitude
    const char* date = "2023-10-05"; // Example date

    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if (mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    int temperature = get_temperature_for_location(latitude, longitude, date);

    if (temperature != -999) {
        printf("Temperature: %d\n", temperature);
    } else {
        printf("No data found or error occurred.\n");
    }

    mysql_close(conn);

    return 0;
}