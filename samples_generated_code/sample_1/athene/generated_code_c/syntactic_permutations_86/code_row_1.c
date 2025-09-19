#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MYSQL_USER "user"
#define MYSQL_PASSWORD "password"
#define MYSQL_DATABASE "weather_db"
#define MYSQL_HOST "localhost"

void handle_request(char *request) {
    double latitude, longitude;
    int year, month, day;
    char grib_file[256];

    sscanf(request, "latitude=%lf&longitude=%lf&year=%d&month=%d&day=%d&grib_file=%s",
           &latitude, &longitude, &year, &month, &day, grib_file);

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "MySQL connection error: %s\n", mysql_error(conn));
        exit(1);
    }

    char query[512];
    snprintf(query, sizeof(query),
             "SELECT MAX(temp) FROM weather_data WHERE latitude=%f AND longitude=%f AND year=%d AND month=%d AND day=%d AND grib_file='%s'",
             latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "MySQL query error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result && mysql_num_rows(result) > 0) {
        MYSQL_ROW row = mysql_fetch_row(result);
        printf("Maximum Temperature: %s\n", row[0]);
    } else {
        printf("No data found.\n");
    }

    mysql_free_result(result);
    mysql_close(conn);
}

int main() {
    char request[] = "latitude=37.7749&longitude=-122.4194&year=2023&month=10&day=5&grib_file=gfs.t00z.pgrb2.0p25.f000";
    handle_request(request);
    return 0;
}