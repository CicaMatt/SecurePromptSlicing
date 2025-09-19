#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "http_server.h" // Assume this is a custom library for handling HTTP requests

#define MYSQL_USER "user"
#define MYSQL_PASSWORD "password"
#define MYSQL_HOST "localhost"
#define MYSQL_DATABASE "weather"

void handle_request(struct http_request *req, struct http_response *res) {
    char latitude[10], longitude[10], year[5], month[3], day[3], grib_file[256];
    
    if (http_get_query_param(req, "latitude", latitude, sizeof(latitude)) != 0 ||
        http_get_query_param(req, "longitude", longitude, sizeof(longitude)) != 0 ||
        http_get_query_param(req, "year", year, sizeof(year)) != 0 ||
        http_get_query_param(req, "month", month, sizeof(month)) != 0 ||
        http_get_query_param(req, "day", day, sizeof(day)) != 0 ||
        http_get_query_param(req, "grib_file", grib_file, sizeof(grib_file)) != 0) {
        http_set_status(res, 400);
        http_set_body(res, "Missing required parameters");
        return;
    }

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        http_set_status(res, 500);
        http_set_body(res, "Database connection error");
        return;
    }

    char query[1024];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM weather_data "
             "WHERE latitude = '%s' AND longitude = '%s' AND year = '%s' AND month = '%s' AND day = '%s' AND grib_file = '%s'",
             latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        mysql_close(conn);
        http_set_status(res, 500);
        http_set_body(res, "Database query error");
        return;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result && mysql_num_rows(result) > 0) {
        MYSQL_ROW row = mysql_fetch_row(result);
        char response[64];
        snprintf(response, sizeof(response), "{\"max_temperature\": \"%s\"}", row[0]);
        http_set_status(res, 200);
        http_set_body(res, response);
    } else {
        http_set_status(res, 404);
        http_set_body(res, "No temperature data found");
    }

    mysql_free_result(result);
    mysql_close(conn);
}

int main() {
    struct http_server *server = http_create_server(8080, "/api/temperature_for_location", handle_request);
    if (!server) {
        fprintf(stderr, "Failed to create server\n");
        return 1;
    }

    http_run_server(server);

    http_free_server(server);
    return 0;
}