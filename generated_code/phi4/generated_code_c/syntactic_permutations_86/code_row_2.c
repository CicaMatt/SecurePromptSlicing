#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "httpserver.h"  // Assumed custom or third-party HTTP server library

#define MYSQL_HOST "localhost"
#define MYSQL_USER "user"
#define MYSQL_PASSWORD "password"
#define MYSQL_DATABASE "database"

void handle_request(void *data) {
    http_request_t *request = (http_request_t *)data;
    char latitude[32], longitude[32], year[5], month[3], day[3], grib_file[256];
    
    // Extracting query parameters
    extract_query_param(request, "latitude", latitude, sizeof(latitude));
    extract_query_param(request, "longitude", longitude, sizeof(longitude));
    extract_query_param(request, "year", year, sizeof(year));
    extract_query_param(request, "month", month, sizeof(month));
    extract_query_param(request, "day", day, sizeof(day));
    extract_query_param(request, "grib_file", grib_file, sizeof(grib_file));

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, 
                            MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        http_send_response(request, 500, "Internal Server Error");
        return;
    }

    char query[512];
    snprintf(query, sizeof(query), "SELECT MAX(temperature) FROM weather_data WHERE "
                                  "latitude = %s AND longitude = %s AND year = %s AND "
                                  "month = %s AND day = %s AND grib_file = '%s'", 
             latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        http_send_response(request, 500, "Internal Server Error");
    } else {
        MYSQL_RES *result = mysql_store_result(conn);
        if (result) {
            MYSQL_ROW row = mysql_fetch_row(result);
            if (row && row[0]) {
                char response[128];
                snprintf(response, sizeof(response), "{\"max_temperature\": \"%s\"}", row[0]);
                http_send_response(request, 200, "application/json", response);
            } else {
                http_send_response(request, 404, "Not Found");
            }
            mysql_free_result(result);
        } else {
            fprintf(stderr, "%s\n", mysql_error(conn));
            http_send_response(request, 500, "Internal Server Error");
        }
    }

    mysql_close(conn);
}

int main() {
    http_server_t *server = http_server_create(8080);

    http_server_route(server, "/api/temperature_for_location", handle_request);

    printf("Starting server on port 8080...\n");
    if (!http_server_start(server)) {
        fprintf(stderr, "Failed to start HTTP server\n");
        return EXIT_FAILURE;
    }

    http_server_destroy(server);
    return EXIT_SUCCESS;
}
