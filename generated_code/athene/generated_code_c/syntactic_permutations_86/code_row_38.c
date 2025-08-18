#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define MYSQL_USER "your_user"
#define MYSQL_PASSWORD "your_password"
#define MYSQL_DATABASE "your_database"
#define MYSQL_HOST "127.0.0.1"

void handle_request(char* latitude, char* longitude, int year, int month, int day, char* grib_file) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[512];
    snprintf(query, sizeof(query), 
             "SELECT MAX(temperature) FROM temperature_data WHERE latitude = '%s' AND longitude = '%s' AND year = %d AND month = %d AND day = %d AND grib_file = '%s'", 
             latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_store_result(conn);
    if ((row = mysql_fetch_row(res)) != NULL) {
        printf("Max Temperature: %s\n", row[0]);
    } else {
        printf("No data found.\n");
    }

    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    // Simulate HTTP request parameters
    char latitude[] = "37.7749";
    char longitude[] = "-122.4194";
    int year = 2023;
    int month = 10;
    int day = 5;
    char grib_file[] = "gfs.t00z.pgrb2full.0p25.f000";

    handle_request(latitude, longitude, year, month, day, grib_file);
    return 0;
}