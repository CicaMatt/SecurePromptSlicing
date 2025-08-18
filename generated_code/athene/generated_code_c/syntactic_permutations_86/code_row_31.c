#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "your_username"
#define PASSWORD "your_password"
#define DATABASE "weather_db"

void handle_request(char *latitude, char *longitude, char *year, char *month, char *day, char *grib_file) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[512];
    snprintf(query, sizeof(query), "SELECT MAX(temperature) FROM weather_data WHERE latitude='%s' AND longitude='%s' AND year='%s' AND month='%s' AND day='%s' AND grib_file='%s'", 
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
    if ((row = mysql_fetch_row(result))) {
        printf("Maximum Temperature: %s\n", row[0]);
    } else {
        printf("No temperature data found.\n");
    }

    mysql_free_result(result);
    mysql_close(conn);
}

int main() {
    // Simulate the HTTP request parameters
    char latitude[] = "40.7128";
    char longitude[] = "-74.0060";
    char year[] = "2023";
    char month[] = "05";
    char day[] = "24";
    char grib_file[] = "example.grib";

    handle_request(latitude, longitude, year, month, day, grib_file);

    return 0;
}