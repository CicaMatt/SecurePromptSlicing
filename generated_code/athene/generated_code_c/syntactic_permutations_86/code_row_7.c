#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void handle_request(char* request) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "weather_db", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char latitude[20];
    char longitude[20];
    char year[5];
    char month[3];
    char day[3];
    char grib_file[100];

    sscanf(request, "latitude=%[^&]&longitude=%[^&]&year=%[^&]&month=%[^&]&day=%[^&]&grib_file=%s",
           latitude, longitude, year, month, day, grib_file);

    char query[500];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM weather_data WHERE "
             "latitude='%s' AND longitude='%s' AND year='%s' AND month='%s' AND day='%s' AND grib_file='%s'",
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
            printf("No data found.\n");
        }
        mysql_free_result(result);
    }

    mysql_close(conn);
}

int main() {
    char request[] = "latitude=37.7749&longitude=-122.4194&year=2023&month=10&day=05&grib_file=gfs.t12z.pgrb2.0p25.f000";
    handle_request(request);
    return 0;
}