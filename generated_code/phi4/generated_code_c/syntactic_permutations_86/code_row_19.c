#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <libwebsockets.h>

#define LISTEN_PORT 7681
#define ENDPOINT "/api/temperature_for_location"
#define MAX_PAYLOAD_SIZE 1024

typedef struct {
    int fd;
    struct lws *wsi;
} per_session_data__simple_t;

static const char *http_header = "HTTP/1.0 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\n";

static int callback_http(struct lws *wsi, enum lws_callback_reasons reason,
                         void *user, void *in, size_t len) {
    switch (reason) {
        case LWS_CALLBACK_HTTP:
            if (!lws_add_http_header_status(wsi, 200)) return -1;
            lws_add_http_header(wsi, "Content-Type", "text/plain", NULL, HTTP_HEADER_END);
            break;
        
        case LWS_CALLBACK_HTTP_BODY_COMPLETION:
            per_session_data__simple_t *pss = (per_session_data__simple_t *)user;
            
            char lat[16], lon[16], year[5], month[3], day[3], grib_file[256];
            if(sscanf((const char*)in, "latitude=%15s&longitude=%15s&year=%4s&month=%2s&day=%2s&grib_file=%255s",
                      lat, lon, year, month, day, grib_file) != 6) {
                lws_write(wsi, (unsigned char*)"Error: Invalid parameters.", sizeof("Error: Invalid parameters.") - 1, LWS_WRITE_TEXT);
                return -1;
            }

            MYSQL *conn = mysql_init(NULL);
            if (!mysql_real_connect(conn, "localhost", "username", "password", "database", 0, NULL, 0)) {
                lws_write(wsi, (unsigned char*)"Error: Could not connect to database.", sizeof("Error: Could not connect to database.") - 1, LWS_WRITE_TEXT);
                mysql_close(conn);
                return -1;
            }

            char query[512];
            snprintf(query, sizeof(query), 
                     "SELECT MAX(temperature) FROM temperature_data WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file='%s'",
                     lat, lon, year, month, day, grib_file);

            if (mysql_query(conn, query)) {
                lws_write(wsi, (unsigned char*)"Error: Query execution failed.", sizeof("Error: Query execution failed.") - 1, LWS_WRITE_TEXT);
            } else {
                MYSQL_RES *result = mysql_store_result(conn);
                if (result) {
                    MYSQL_ROW row = mysql_fetch_row(result);
                    if (row && row[0]) {
                        lws_write(wsi, (unsigned char*)row[0], strlen(row[0]), LWS_WRITE_TEXT);
                    } else {
                        lws_write(wsi, (unsigned char*)"Error: No data found.", sizeof("Error: No data found.") - 1, LWS_WRITE_TEXT);
                    }
                    mysql_free_result(result);
                }
            }

            mysql_close(conn);
            break;

        case LWS_CALLBACK_HTTP_WRITEABLE:
            lws_write_http_chunk(wsi, (unsigned char*)http_header, strlen(http_header), 1);
            return -1; // We're done now

        default:
            break;
    }
    return 0;
}

static struct lws_protocols protocols[] = {
    { ENDPOINT, callback_http, sizeof(per_session_data__simple_t), 4096 },
    { NULL, NULL, 0, 0 } /* terminator */
};

int main(void) {
    struct lws_context_creation_info info;
    memset(&info, 0, sizeof(info));
    info.port = LISTEN_PORT;
    info.protocols = protocols;

    struct lws_context *context = lws_create_context(&info);
    if (!context) return -1;

    while (1)
        lws_service(context, 100);

    lws_context_destroy(context);
    return 0;
}