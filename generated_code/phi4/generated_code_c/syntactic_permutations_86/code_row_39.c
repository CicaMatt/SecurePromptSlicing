#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <arpa/inet.h>
#include "mongoose.h"

static struct mg_serve_http_opts s_http_server_opts;

void handle_request(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev != MG_EV_HTTP_REQUEST)
        return;

    struct http_message *hm = (struct http_message *) ev_data;
    char query[256] = {0};
    char latitude[10], year[5], month[3], day[3], grib_file[50];

    // Extract parameters from request
    if (mg_get_var(hm, "latitude", latitude, sizeof(latitude)) &&
        mg_get_var(hm, "year", year, sizeof(year)) &&
        mg_get_var(hm, "month", month, sizeof(month)) &&
        mg_get_var(hm, "day", day, sizeof(day)) &&
        mg_get_var(hm, "grib_file", grib_file, sizeof(grib_file))) {

        snprintf(query, sizeof(query), 
                 "SELECT MAX(temperature) FROM temperature_data "
                 "WHERE latitude = '%s' AND year = %s AND month = %s AND day = %s AND grib_file = '%s';",
                 latitude, year, month, day, grib_file);

        MYSQL *conn;
        MYSQL_RES *res;
        MYSQL_ROW row;

        conn = mysql_init(NULL);
        if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
            mg_printf(nc, "%s", "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nDatabase connection failed");
            return;
        }

        if (mysql_query(conn, query)) {
            mg_printf(nc, "%s", "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nQuery execution failed");
            mysql_close(conn);
            return;
        }

        res = mysql_store_result(conn);

        if (!res) {
            mg_printf(nc, "%s", "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nFailed to retrieve data");
            mysql_close(conn);
            return;
        }

        row = mysql_fetch_row(res);

        if (row && row[0]) {
            mg_send_head(nc, 200, strlen(row[0]), "Content-Type: application/json");
            mg_printf(nc, "{\"max_temperature\": \"%s\"}", row[0]);
        } else {
            mg_send_head(nc, 404, 0, "Content-Type: text/plain");
            mg_printf(nc, "No data found for the given parameters");
        }

        mysql_free_result(res);
        mysql_close(conn);
    } else {
        mg_send_head(nc, 400, 0, "Content-Type: text/plain");
        mg_printf(nc, "Bad Request: Missing parameters");
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, "http://localhost:8080", handle_request);
    if (nc == NULL) {
        fprintf(stderr, "Failed to create listener\n");
        return 1;
    }

    s_http_server_opts.document_root = "."; 
    s_http_server_opts.enable_directory_listing = "yes";

    mg_set_protocol_http_websocket(nc);
    printf("Starting web server on port %d\n", 8080);

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);

    return 0;
}
