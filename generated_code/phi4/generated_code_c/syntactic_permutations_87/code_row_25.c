#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "weather_db"

// Function declarations
float temperature_for_location(double latitude, double longitude, const char *date);

int main() {
    // Example usage
    double lat = 40.7128;
    double lon = -74.0060;
    const char *date = "2023-10-01";

    float temp = temperature_for_location(lat, lon, date);
    if (temp != -1) {
        printf("Temperature: %.2f\n", temp);
    } else {
        printf("Error retrieving temperature.\n");
    }

    return 0;
}

float temperature_for_location(double latitude, double longitude, const char *date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM weather_data WHERE latitude = %f AND longitude = %f AND date = '%s'", latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    res = mysql_use_result(conn);

    float temperature = -1.0;
    while ((row = mysql_fetch_row(res))) {
        temperature = atof(row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}
