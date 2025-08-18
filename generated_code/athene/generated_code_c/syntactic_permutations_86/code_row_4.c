#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "http_server.h" // Assuming an HTTP server library is available

#define DB_HOST "localhost"
#define DB_USER "user"
#define DB_PASS "password"
#define DB_NAME "weather_db"

void handle_request(HttpRequest *req, HttpResponse *res) {
    char latitude[10], longitude[10], year[5], month[3], day[3], grib_file[256];
    
    http_get_query_param(req, "latitude", latitude, sizeof(latitude));
    http_get_query_param(req, "longitude", longitude, sizeof(longitude));
    http_get_query_param(req, "year", year, sizeof(year));
    http_get_query_param(req, "month", month, sizeof(month));
    http_get_query_param(req, "day", day, sizeof(day));
    http_get_query_param(req, "grib_file", grib_file, sizeof(grib_file));

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        http_set_status(res, 500);
        http_set_body(res, "Database connection failed");
        return;
    }

    char query[1024];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM weather_data "
             "WHERE latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = '%s'",
             latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        mysql_close(conn);
        http_set_status(res, 500);
        http_set_body(res, "Query execution failed");
        return;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        mysql_close(conn);
        http_set_status(res, 500);
        http_set_body(res, "Failed to store result");
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    char max_temp[10] = "Unknown";
    if (row && row[0]) {
        strcpy(max_temp, row[0]);
    }

    mysql_free_result(result);
    mysql_close(conn);

    http_set_status(res, 200);
    http_set_header(res, "Content-Type", "application/json");
    char response[128];
    snprintf(response, sizeof(response), "{\"max_temperature\": \"%s\"}", max_temp);
    http_set_body(res, response);
}

int main() {
    HttpServer *server = http_create_server(8080);
    http_add_route(server, "/api/temperature_for_location", handle_request);
    http_start_server(server);
    return 0;
}