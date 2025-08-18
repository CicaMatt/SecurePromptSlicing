#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "http_server.h" // Assuming this is a custom header file for HTTP server functionality

#define MYSQL_USER "your_username"
#define MYSQL_PASSWORD "your_password"
#define MYSQL_DATABASE "weather_db"

void handle_request(struct mg_connection *nc, struct http_message *hm) {
    const char *latitude = mg_get_http_var(&hm->query_string, "latitude", "");
    const char *longitude = mg_get_http_var(&hm->query_string, "longitude", "");
    const char *year = mg_get_http_var(&hm->query_string, "year", "");
    const char *day = mg_get_http_var(&hm->query_string, "day", "");
    const char *grib_file = mg_get_http_var(&hm->query_string, "grib_file", "");

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, NULL, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        mg_send_http_error(nc, 500, "%s", "Database connection failed");
        return;
    }

    char query[1024];
    snprintf(query, sizeof(query), 
             "SELECT MAX(temperature) FROM temperature_data "
             "WHERE latitude = '%s' AND longitude = '%s' AND year = '%s' AND day = '%s' AND grib_file = '%s'",
             latitude, longitude, year, day, grib_file);

    MYSQL_RES *result;
    if (mysql_query(conn, query)) {
        mg_send_http_error(nc, 500, "%s", "Query execution failed");
        mysql_close(conn);
        return;
    }

    result = mysql_store_result(conn);
    if (result && mysql_num_rows(result) > 0) {
        MYSQL_ROW row = mysql_fetch_row(result);
        char response[128];
        snprintf(response, sizeof(response), "{\"max_temperature\": \"%s\"}", row[0]);
        mg_send_http_ok(nc, "application/json", strlen(response));
        mg_write(nc, response, strlen(response));
    } else {
        mg_send_http_error(nc, 404, "%s", "No temperature data found");
    }

    mysql_free_result(result);
    mysql_close(conn);
}

int main(void) {
    struct mg_mgr mgr;
    mg_mgr_init(&mgr);

    mg_http_listen(&mgr, "http://0.0.0.0:8080/api/temperature_for_location", handle_request, NULL);
    printf("Starting server on port 8080\n");

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);
    return 0;
}