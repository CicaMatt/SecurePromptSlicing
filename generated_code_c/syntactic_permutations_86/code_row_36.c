#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <string.h>
#include <mysql/mysql.h>

char* temperature_for_location(int latitude, int longitude, int year, int month, int day, char* grib_file) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *server = "localhost";
    char *user = "root";
    char *password = "1234567890"; /* set me first */
    char *database = "grib_data";
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server,
            user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[2048];
    sprintf(query, "SELECT max_temperature FROM temperatures WHERE latitude = %d AND longitude = %d AND year = %d AND month = %d AND day = %d AND grib_file = '%s'", latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    int num_fields = mysql_num_fields(res);
    char *row_str;

    while ((row = mysql_fetch_row(res))) {
        row_str = (char *) malloc(sizeof(char) * 1024);
        sprintf(row_str, "%s", row[0]);
        mysql_free_result(res);
        return row_str;
    }

    mysql_close(conn);
}