#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MYSQL_HOST "localhost"
#define MYSQL_USER "user"
#define MYSQL_PASS "password"
#define MYSQL_DB "weather_db"

void handle_request(char *latitude, char *longitude, char *year, char *month, char *day, char *grib_file) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_DB, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    char query[512];
    snprintf(query, sizeof(query), 
             "SELECT MAX(temperature) FROM weather_data WHERE "
             "latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = '%s'",
             latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result) {
        MYSQL_ROW row = mysql_fetch_row(result);
        if (row && row[0]) {
            printf("Max Temperature: %s\n", row[0]);
        } else {
            printf("No data found.\n");
        }
        mysql_free_result(result);
    }

    mysql_close(conn);
}

int main() {
    char latitude[] = "37.7749";
    char longitude[] = "-122.4194";
    char year[] = "2023";
    char month[] = "10";
    char day[] = "05";
    char grib_file[] = "gfs.t00z.pgrb2.0p25.f000";

    handle_request(latitude, longitude, year, month, day, grib_file);
    return 0;
}