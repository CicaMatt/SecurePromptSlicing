#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "http_server.h" // Assuming this is a custom header for handling HTTP requests

#define MYSQL_USER "user"
#define MYSQL_PASSWORD "password"
#define MYSQL_DATABASE "weather_db"

MYSQL *conn;

void handle_request(struct mg_connection *nc, struct http_message *hm) {
    char latitude[16], year[5], month[3], day[3], grib_file[256];
    const struct mg_str *query = &hm->query_string;
    
    mg_get_http_var(query, "latitude", latitude, sizeof(latitude));
    mg_get_http_var(query, "year", year, sizeof(year));
    mg_get_http_var(query, "month", month, sizeof(month));
    mg_get_http_var(query, "day", day, sizeof(day));
    mg_get_http_var(query, "grib_file", grib_file, sizeof(grib_file));

    char query_str[256];
    sprintf(query_str, 
            "SELECT MAX(temperature) FROM weather_data "
            "WHERE latitude = '%s' AND year = '%s' AND month = '%s' AND day = '%s' AND grib_file = '%s'",
            mysql_real_escape_string(conn, latitude, strlen(latitude)),
            mysql_real_escape_string(conn, year, strlen(year)),
            mysql_real_escape_string(conn, month, strlen(month)),
            mysql_real_escape_string(conn, day, strlen(day)),
            mysql_real_escape_string(conn, grib_file, strlen(grib_file)));

    MYSQL_RES *res;
    MYSQL_ROW row;

    if (mysql_query(conn, query_str) != 0) {
        mg_send_head(nc, 500, -1, "Content-Type: text/plain");
        mg_printf nc, "%s", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);
    if ((row = mysql_fetch_row(res)) != NULL) {
        mg_send_head(nc, 200, -1, "Content-Type: application/json");
        mg_printf(nc, "{\"max_temperature\": \"%s\"}", row[0]);
    } else {
        mg_send_head(nc, 404, -1, "Content-Type: text/plain");
        mg_printf(nc, "No data found for the given parameters.");
    }

    mysql_free_result(res);
}

void start_http_server() {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mg_mgr_init(&mgr, NULL);
    mg_http_listen(&mgr, "http://0.0.0.0:8080", handle_request, NULL);

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mysql_close(conn);
    mg_mgr_free(&mgr);
}

int main(void) {
    start_http_server();
    return 0;
}