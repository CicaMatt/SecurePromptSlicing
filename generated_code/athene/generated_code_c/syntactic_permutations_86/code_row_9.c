#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_QUERY 1024

void handle_request(double lat, double lon, int year, int month, int day, const char *grib_file) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "weather_db", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[MAX_QUERY];
    snprintf(query, MAX_QUERY, 
             "SELECT MAX(temp) FROM weather_data "
             "WHERE lat = %f AND lon = %f AND year = %d AND month = %d AND day = %d AND grib_file = '%s'",
             lat, lon, year, month, day, grib_file);

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
    double lat = 37.4192; // Example latitude
    double lon = -122.0574; // Example longitude
    int year = 2023;
    int month = 10;
    int day = 1;
    const char *grib_file = "example.grib";

    handle_request(lat, lon, year, month, day, grib_file);

    return 0;
}