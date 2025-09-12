#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD "password"
#define DATABASE "weatherdb"

void handle_request(char *latitude, char *longitude, char *year, char *month, char *day, char *grib_file) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[1024];
    int temperature;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    snprintf(query, sizeof(query), 
             "SELECT MAX(temperature) FROM temperature_data WHERE "
             "latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = '%s'",
             latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_store_result(conn);
    if ((row = mysql_fetch_row(res))) {
        temperature = atoi(row[0]);
        printf("Maximum Temperature: %d\n", temperature);
    } else {
        printf("No data found\n");
    }

    mysql_free_result(res);
    mysql_close(conn);
}

int main(int argc, char **argv) {
    // Simulate request handling
    char *latitude = "40.7128";
    char *longitude = "-74.0060";
    char *year = "2023";
    char *month = "05";
    char *day = "21";
    char *grib_file = "file.grib";

    handle_request(latitude, longitude, year, month, day, grib_file);
    return 0;
}