#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "http_parser.h"
#include <pthread.h>

#define MYSQL_HOST "localhost"
#define MYSQL_USER "root"
#define MYSQL_PASSWORD ""
#define MYSQL_DATABASE "weather_db"

typedef struct {
    char latitude[10];
    char year[5];
    char month[3];
    char day[3];
    char grib_file[100];
} RequestParams;

void *handle_request(void *arg) {
    http_parser parser;
    http_parser_settings settings = {0};
    
    char buffer[1024] = {0};
    fread(buffer, 1, sizeof(buffer), stdin);

    if (http_parser_init(&parser, HTTP_REQUEST)) {
        return NULL;
    }

    settings.on_url = [](http_parser *p, const char *at, size_t length) -> int {
        RequestParams params;
        sscanf(at, "latitude=%[^&]&year=%[^&]&month=%[^&]&day=%[^&]&grib_file=%s", 
               params.latitude, params.year, params.month, params.day, params.grib_file);
        
        MYSQL *conn = mysql_init(NULL);
        if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD,
                                MYSQL_DATABASE, 0, NULL, 0)) {
            fprintf(stderr, "Database connection failed: %s\n", mysql_error(conn));
            return 1;
        }

        char query[256];
        snprintf(query, sizeof(query), 
                 "SELECT MAX(temperature) FROM temperatures WHERE "
                 "latitude = '%s' AND year = '%s' AND month = '%s' AND day = '%s' AND grib_file = '%s'",
                 params.latitude, params.year, params.month, params.day, params.grib_file);

        if (mysql_query(conn, query)) {
            fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
        } else {
            MYSQL_RES *result = mysql_store_result(conn);
            if (result) {
                MYSQL_ROW row = mysql_fetch_row(result);
                if (row && row[0]) {
                    printf("HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n");
                    printf("{\"max_temperature\": \"%s\"}", row[0]);
                } else {
                    printf("HTTP/1.1 404 Not Found\r\nContent-Type: application/json\r\n\r\n");
                    printf("{\"error\": \"No temperature data found\"}");
                }
                mysql_free_result(result);
            } else {
                fprintf(stderr, "Result set not available: %s\n", mysql_error(conn));
            }
        }

        mysql_close(conn);

        return 0;
    };

    settings.url_callback = (http_parser_url_cb)settings.on_url;

    if (http_parser_execute(&parser, &settings, buffer, strlen(buffer))) {
        fprintf(stderr, "Parse error: %s\n", http_errno_name(parser.http_errno));
    }

    return NULL;
}

int main() {
    pthread_t thread_id;
    if (pthread_create(&thread_id, NULL, handle_request, NULL)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    pthread_join(thread_id, NULL);
    return 0;
}