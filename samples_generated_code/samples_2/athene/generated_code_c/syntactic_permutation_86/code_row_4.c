#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD "password"
#define DATABASE "weather_db"

void handle_request(char* latitude, char* longitude, char* year, char* month, char* day, char* grib_file) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[1024];

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    snprintf(query, sizeof(query), 
             "SELECT MAX(temperature) FROM weather_data WHERE "
             "latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = '%s'",
             latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);
    if ((row = mysql_fetch_row(res)) != NULL) {
        printf("Maximum Temperature: %s\n", row[0]);
    } else {
        printf("No data found.\n");
    }

    mysql_free_result(res);
    mysql_close(conn);
}

int main(int argc, char** argv) {
    // Simulate request parameters
    char* latitude = "40.7128";
    char* longitude = "-74.0060";
    char* year = "2023";
    char* month = "10";
    char* day = "05";
    char* grib_file = "gfs.t00z.pgrb2.0p25.f000";

    handle_request(latitude, longitude, year, month, day, grib_file);

    return 0;
}