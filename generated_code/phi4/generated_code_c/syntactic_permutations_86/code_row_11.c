#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <libwebsockets.h>

#define ADDRESS "localhost"
#define PORT 8080

static int callback_http(struct lws *wsi, enum lws_callback_reasons reason,
                         void *user, void *in, size_t len) {
    if (reason == LWS_CALLBACK_HTTP) {
        char path[256];
        const struct lws_token_exts *token;
        lws_tokenize_url(lws_hdr_total_length(wsi), lws_get_http_header(wsi->parent),
                         wsi->http_status_line, sizeof(path), &token, path, sizeof(path));
        if (strcmp(path + 1, "api/temperature_for_location") == 0) {
            char lat[16], lon[16], year[5], month[3], day[3], grib_file[256];
            
            // Extract query parameters
            char *query = strstr(lws_get_http_header(wsi->parent), "?");
            if (query) {
                sscanf(query + 1, "latitude=%15s&longitude=%15s&year=%4s&month=%2s&day=%2s&grib_file=%255s",
                       lat, lon, year, month, day, grib_file);
            }

            // Connect to MySQL
            MYSQL *conn = mysql_init(NULL);
            if (!mysql_real_connect(conn, ADDRESS, "username", "password", "database_name", 0, NULL, 0)) {
                fprintf(stderr, "%s\n", mysql_error(conn));
                return -1;
            }

            char query_str[512];
            snprintf(query_str, sizeof(query_str),
                     "SELECT MAX(temperature) FROM temperature_data WHERE latitude=%s AND longitude=%s "
                     "AND year=%s AND month=%s AND day=%s AND grib_file='%s'",
                     lat, lon, year, month, day, grib_file);

            if (mysql_query(conn, query_str)) {
                fprintf(stderr, "%s\n", mysql_error(conn));
                mysql_close(conn);
                return -1;
            }

            MYSQL_RES *result = mysql_store_result(conn);
            if (!result) {
                fprintf(stderr, "%s\n", mysql_error(conn));
                mysql_close(conn);
                return -1;
            }

            MYSQL_ROW row = mysql_fetch_row(result);
            char response[256];
            snprintf(response, sizeof(response),
                     "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"
                     "Max Temperature: %s", row ? row[0] : "N/A");

            lws_write(wsi, (unsigned char *)response, strlen(response), LWS_WRITE_HTTP);

            mysql_free_result(result);
            mysql_close(conn);
        }
    }
    return 0;
}

static struct lws_protocols protocols[] = {
    { "http", callback_http, sizeof(struct per_session_data__http), 128 },
    { NULL, NULL, 0, 0 } // terminator
};

int main() {
    struct lws_context_creation_info info;
    memset(&info, 0, sizeof(info));
    info.port = PORT;
    info.protocols = protocols;

    struct lws_context *context = lws_create_context(&info);
    if (!context) {
        fprintf(stderr, "lws init failed\n");
        return -1;
    }

    while (1) {
        lws_service(context, 1000);
    }

    lws_context_destroy(context);
    return 0;
}
