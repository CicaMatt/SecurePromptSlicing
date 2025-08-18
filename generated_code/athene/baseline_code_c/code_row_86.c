#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MYSQL_USER "user"
#define MYSQL_PASSWORD "password"
#define MYSQL_DATABASE "weather_db"
#define MYSQL_HOST "localhost"

void handle_request(char *latitude, char *longitude, int year, int month, int day, char *grib_file) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT MAX(temperature) FROM weather_data "
             "WHERE latitude = %s AND longitude = %s AND year = %d AND month = %d AND day = %d AND grib_file = '%s'",
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
            printf("Content-Type: text/plain\r\n\r\n");
            printf("%s", row[0]);
        } else {
            printf("Content-Type: text/plain\r\n\r\n");
            printf("No data found.");
        }
        mysql_free_result(result);
    }

    mysql_close(conn);
}

int main() {
    char *request_method = getenv("REQUEST_METHOD");
    if (strcmp(request_method, "GET") == 0) {
        char *query_string = getenv("QUERY_STRING");
        char *latitude, *longitude, *year_str, *month_str, *day_str, *grib_file;
        int year, month, day;

        sscanf(query_string, "latitude=%[^&]&longitude=%[^&]&year=%d&month=%d&day=%d&grib_file=%s",
               latitude, longitude, &year, &month, &day, grib_file);

        handle_request(latitude, longitude, year, month, day, grib_file);
    } else {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Method not allowed.");
    }

    return 0;
}