#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "cgi.h"

void handle_request() {
    char *latitude = getenv("QUERY_LATITUDE");
    char *longitude = getenv("QUERY_LONGITUDE");
    char *year = getenv("QUERY_YEAR");
    char *month = getenv("QUERY_MONTH");
    char *day = getenv("QUERY_DAY");
    char *grib_file = getenv("QUERY_GRIB_FILE");

    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Failed to connect to database\n");
        return;
    }

    char query[1024];
    snprintf(query, sizeof(query), 
             "SELECT MAX(temperature) FROM weather_data WHERE "
             "latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = '%s'",
             latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Query execution failed\n");
        mysql_close(conn);
        return;
    }

    res = mysql_store_result(conn);
    if (res) {
        row = mysql_fetch_row(res);
        if (row && row[0]) {
            printf("Content-Type: application/json\r\n\r\n");
            printf("{\"max_temperature\": \"%s\"}", row[0]);
        } else {
            printf("Content-Type: application/json\r\n\r\n");
            printf("{\"error\": \"No data found\"}");
        }
        mysql_free_result(res);
    } else {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Failed to retrieve result set\n");
    }

    mysql_close(conn);
}

int main() {
    cgiInit();
    handle_request();
    return 0;
}