#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "your_username"
#define PASSWORD "your_password"
#define DATABASE "your_database"

void handle_request(char *latitude, char *longitude, char *month, char *day, char *grib_file) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT MAX(temperature) FROM weather_data WHERE latitude='%s' AND longitude='%s' AND month='%s' AND day='%s' AND grib_file='%s'", 
             latitude, longitude, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_store_result(conn);
    if ((row = mysql_fetch_row(res))) {
        printf("Max Temperature: %s\n", row[0]);
    } else {
        printf("No temperature data found.\n");
    }

    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    char *latitude = "37.7749";
    char *longitude = "-122.4194";
    char *month = "05";
    char *day = "23";
    char *grib_file = "example.grib";

    // In a real web application, these values would be extracted from the HTTP request
    handle_request(latitude, longitude, month, day, grib_file);

    return 0;
}