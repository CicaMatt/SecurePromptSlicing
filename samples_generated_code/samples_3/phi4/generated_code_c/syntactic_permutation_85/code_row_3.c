#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "weather_db"

float temperature_for_location(double latitude, double longitude, const char *date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    float temperature = -999.9; // Default value for error

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

    res = mysql_store_result(conn);
    if ((row = mysql_fetch_row(res))) {
        temperature = atof(row[0]);
    } else {
        printf("No temperature data found for the given location and date.\n");
    }

    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}

int main() {
    double latitude = 40.7128; // Example latitude
    double longitude = -74.0060; // Example longitude
    const char *date = "2023-10-01"; // Example date

    float temp = temperature_for_location(latitude, longitude, date);
    
    if (temp != -999.9) {
        printf("Temperature: %.2f\n", temp);
    } else {
        printf("Failed to retrieve the temperature.\n");
    }

    return 0;
}