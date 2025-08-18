#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "mongoose.h"

static struct mg_serve_http_opts shttp_opts;

void handle_request(struct mg_connection *conn, int ev, void *ev_data, void *fn_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;

        char latitude[16], longitude[16], year[5], month[3], day[3], grib_file[256];
        sscanf(hm->body.p, "latitude=%15s&longitude=%15s&year=%4s&month=%2s&day=%2s&grib_file=%255s",
               latitude, longitude, year, month, day, grib_file);

        char query[512];
        snprintf(query, sizeof(query),
                 "SELECT MAX(temperature) FROM temperature_data WHERE "
                 "latitude = '%s' AND longitude = '%s' AND year = '%s' AND month = '%s' AND day = '%s' AND grib_file = '%s';",
                 latitude, longitude, year, month, day, grib_file);

        MYSQL *conn;
        conn = mysql_init(NULL);
        if (!mysql_real_connect(conn, "localhost", "root", "", "weather_db", 0, NULL, 0)) {
            char response[256];
            snprintf(response, sizeof(response),
                     "{\"error\": \"Database connection failed: %s\"}", mysql_error(conn));
            mg_http_reply(conn, 500, "Content-Type: application/json\n", response);
            return;
        }

        if (mysql_query(conn, query)) {
            char response[256];
            snprintf(response, sizeof(response),
                     "{\"error\": \"Query execution failed: %s\"}", mysql_error(conn));
            mg_http_reply(conn, 400, "Content-Type: application/json\n", response);
            mysql_close(conn);
            return;
        }

        MYSQL_RES *result = mysql_store_result(conn);
        if (!result) {
            char response[256];
            snprintf(response, sizeof(response),
                     "{\"error\": \"Failed to retrieve results: %s\"}", mysql_error(conn));
            mg_http_reply(conn, 500, "Content-Type: application/json\n", response);
            mysql_close(conn);
            return;
        }

        MYSQL_ROW row = mysql_fetch_row(result);
        if (row) {
            char response[256];
            snprintf(response, sizeof(response), "{\"max_temperature\": \"%s\"}", row[0]);
            mg_http_reply(conn, 200, "Content-Type: application/json\n", response);
        } else {
            char response[] = "{\"error\": \"No data found.\"}";
            mg_http_reply(conn, 404, "Content-Type: application/json\n", response);
        }

        mysql_free_result(result);
        mysql_close(conn);
    }
}

int main(void) {
    struct mg_mgr mgr;
    mg_mgr_init(&mgr, NULL);

    struct mg_connection *nc = mg_bind(&mgr, "0.0.0.0", 8080,
                                       handle_request, &shttp_opts);
    if (nc == NULL) {
        printf("Failed to create listener\n");
        return 1;
    }

    printf("Starting web server on http://0.0.0.0:8080/\nPress Enter key to stop...\n");

    getchar();

    mg_mgr_free(&mgr);

    return 0;
}