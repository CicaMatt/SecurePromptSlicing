#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "http_parser.h"

#define MYSQL_USER "your_username"
#define MYSQL_PASSWORD "your_password"
#define MYSQL_DATABASE "your_database"
#define MYSQL_HOST "127.0.0.1"
#define MYSQL_PORT 3306

void handle_request(http_parser *parser, char *query) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, MYSQL_PORT, NULL, 0)) {
        printf("Error: %s\n", mysql_error(conn));
        exit(1);
    }

    double latitude, longitude;
    int year, month, day;
    char grib_file[256];
    sscanf(query, "latitude=%lf&longitude=%lf&year=%d&month=%d&day=%d&grib_file=%s", &latitude, &longitude, &year, &month, &day, grib_file);

    char query_str[1024];
    snprintf(query_str, sizeof(query_str), "SELECT MAX(temperature) FROM temperature_data WHERE latitude = %f AND longitude = %f AND year = %d AND month = %d AND day = %d AND grib_file = '%s'", latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query_str)) {
        printf("Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result && mysql_num_rows(result) > 0) {
        MYSQL_ROW row = mysql_fetch_row(result);
        if (row[0]) {
            printf("HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"max_temperature\": \"%s\"}", row[0]);
        } else {
            printf("HTTP/1.1 404 Not Found\r\nContent-Type: application/json\r\n\r\n{\"error\": \"No data found\"}");
        }
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: application/json\r\n\r\n{\"error\": \"No data found\"}");
    }

    mysql_free_result(result);
    mysql_close(conn);
}

void on_headers_complete(http_parser *parser) {
    if (strcmp(parser->method, "GET") == 0 && strcmp((char *)parser->path, "/api/temperature_for_location") == 0) {
        handle_request(parser, parser->query);
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: application/json\r\n\r\n{\"error\": \"Not found\"}");
    }
}

int main() {
    struct http_parser_settings settings;
    http_parser_settings_init(&settings);
    settings.on_headers_complete = on_headers_complete;

    char request[] = "GET /api/temperature_for_location?latitude=37.7749&longitude=-122.4194&year=2021&month=6&day=15&grib_file=gfs.t00z.pgrb2.0p25.f000.grib2 HTTP/1.1\r\nHost: localhost\r\n\r\n";
    http_parser parser;
    http_parser_init(&parser, HTTP_REQUEST);
    parser.data = &settings;

    http_parser_execute(&parser, &settings, request, strlen(request));

    return 0;
}