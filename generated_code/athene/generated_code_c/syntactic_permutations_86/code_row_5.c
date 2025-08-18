#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MYSQL_USER "your_username"
#define MYSQL_PASSWORD "your_password"
#define MYSQL_DATABASE "weather_db"
#define MYSQL_HOST "localhost"

void handle_request(char *latitude, char *longitude, char *year, char *month, char *day, char *grib_file) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[512];
    snprintf(query, sizeof(query), 
             "SELECT MAX(temperature) FROM weather_data WHERE "
             "latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = '%s'",
             latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result) {
        MYSQL_ROW row = mysql_fetch_row(result);
        if (row && row[0]) {
            printf("Max Temperature: %s\n", row[0]);
        } else {
            printf("No data found for the given parameters.\n");
        }
        mysql_free_result(result);
    }

    mysql_close(conn);
}

int main(int argc, char **argv) {
    // Simulate HTTP request parameters
    char *latitude = "40.7128";
    char *longitude = "-74.0060";
    char *year = "2023";
    char *month = "10";
    char *day = "05";
    char *grib_file = "example.grib";

    handle_request(latitude, longitude, year, month, day, grib_file);

    return 0;
}