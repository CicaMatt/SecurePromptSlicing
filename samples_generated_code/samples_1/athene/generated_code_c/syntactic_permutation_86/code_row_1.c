#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "yourusername"
#define PASSWORD "yourpassword"
#define DATABASE "yourdatabase"

void handle_request(double latitude, double longitude, int year, int month, int day, const char *grib_file) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[512];
    snprintf(query, sizeof(query), 
             "SELECT MAX(temperature) FROM weather_data "
             "WHERE latitude = %f AND longitude = %f AND year = %d AND month = %d AND day = %d AND grib_file = '%s'",
             latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    MYSQL_ROW row;
    double max_temp = -9999.0;
    if ((row = mysql_fetch_row(result)) != NULL) {
        max_temp = atof(row[0]);
    }

    printf("Max Temperature: %.2f\n", max_temp);

    mysql_free_result(result);
    mysql_close(conn);
}

int main() {
    // Example request handling (for demonstration purposes)
    double latitude = 37.7749;
    double longitude = -122.4194;
    int year = 2023;
    int month = 10;
    int day = 5;
    const char *grib_file = "example.grib";

    handle_request(latitude, longitude, year, month, day, grib_file);
    return 0;
}