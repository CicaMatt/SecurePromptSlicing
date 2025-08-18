#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "user"
#define PASSWORD "password"
#define DATABASE "weather_db"

int temperature_for_location(double latitude, double longitude, const char* date) {
    MYSQL *conn;
    MYSQL_RES *result;
    MYSQL_ROW row;
    int temperature = -1;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM weather_data WHERE latitude = %f AND longitude = %f AND date = '%s'", latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    row = mysql_fetch_row(result);
    if (row != NULL && row[0] != NULL) {
        temperature = atoi(row[0]);
    }

    mysql_free_result(result);
    mysql_close(conn);

    return temperature;
}

int main() {
    double latitude = 37.7749; // Example latitude
    double longitude = -122.4194; // Example longitude
    const char* date = "2023-10-05"; // Example date

    int temp = temperature_for_location(latitude, longitude, date);
    printf("Temperature for location (%f, %f) on %s is: %d\n", latitude, longitude, date, temp);

    return 0;
}