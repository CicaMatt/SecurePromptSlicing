#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "http_parser.h"

#define PORT 8080
#define MYSQL_USER "user"
#define MYSQL_PASSWORD "password"
#define MYSQL_DB "weather_db"
#define MYSQL_HOST "localhost"

void handle_request(http_parser* parser, MYSQL* conn) {
    char query[256];
    double latitude, longitude;
    int year, month, day;
    char grib_file[100];

    sscanf(parser->query, "?latitude=%lf&longitude=%lf&year=%d&month=%d&day=%d&grib_file=%99s",
           &latitude, &longitude, &year, &month, &day, grib_file);

    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM weather_data "
             "WHERE latitude = %lf AND longitude = %lf AND year = %d AND month = %d AND day = %d AND grib_file = '%s'",
             latitude, longitude, year, month, day, grib_file);

    MYSQL_RES *result;
    MYSQL_ROW row;

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    result = mysql_store_result(conn);
    if (result && (row = mysql_fetch_row(result))) {
        char response[64];
        snprintf(response, sizeof(response), "Maximum temperature: %s", row[0]);
        http_parser_send_response(parser, 200, response);
    } else {
        http_parser_send_response(parser, 404, "No data found");
    }

    mysql_free_result(result);
}

int main() {
    MYSQL *conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DB, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    http_parser_start_server(PORT, "/api/temperature_for_location", handle_request);

    mysql_close(conn);
    return 0;
}