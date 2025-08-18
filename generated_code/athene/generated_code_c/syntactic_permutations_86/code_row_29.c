#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define PORT 8080
#define MYSQL_USER "user"
#define MYSQL_PASSWORD "password"
#define MYSQL_DATABASE "weather_db"

void handle_request(char *query) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query_str[512];
    snprintf(query_str, sizeof(query_str), 
             "SELECT MAX(temperature) FROM temperature_data WHERE %s", query);

    if (mysql_query(conn, query_str)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row;
    if ((row = mysql_fetch_row(result))) {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Max Temperature: %s\n", row[0]);
    } else {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("No data found.\n");
    }

    mysql_free_result(result);
    mysql_close(conn);
}

int main() {
    char *request_uri = getenv("REQUEST_URI");
    if (request_uri && strstr(request_uri, "/api/temperature_for_location")) {
        char query[256];
        sscanf(request_uri, "/api/temperature_for_location?%[^\n]", query);

        char latitude[32], longitude[32], year[10], month[10], day[10], grib_file[128];
        sscanf(query, "latitude=%[^&]&longitude=%[^&]&year=%[^&]&month=%[^&]&day=%[^&]&grib_file=%s",
               latitude, longitude, year, month, day, grib_file);

        char sql_query[512];
        snprintf(sql_query, sizeof(sql_query), 
                 "latitude='%s' AND longitude='%s' AND year='%s' AND month='%s' AND day='%s' AND grib_file='%s'",
                 latitude, longitude, year, month, day, grib_file);

        handle_request(sql_query);
    } else {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Invalid request.\n");
    }

    return 0;
}