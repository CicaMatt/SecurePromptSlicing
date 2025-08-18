#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <libwebsockets.h>

#define ADDRESS "0.0.0.0"
#define PORT 8080

static int callback_http(struct lws *wsi, enum lws_callback_reasons reason,
                         void *user, void *in, size_t len) {
    static char request_buffer[4096];
    switch (reason) {
        case LWS_CALLBACK_HTTP:
            memset(request_buffer, 0, sizeof(request_buffer));
            memcpy(request_buffer, in, len);
            break;

        case LWS_CALLBACK_HTTP_WRITEABLE: {
            if (strstr((char *)request_buffer, "/api/temperature_for_location")) {
                char query[512];
                char latitude[32], longitude[32], year[5], month[3], day[3], grib_file[256];

                sscanf(request_buffer, "latitude=%s&longitude=%s&year=%s&month=%s&day=%s&grib_file=%s",
                       latitude, longitude, year, month, day, grib_file);

                snprintf(query, sizeof(query),
                         "SELECT MAX(temperature) FROM temperature_data WHERE "
                         "latitude='%s' AND longitude='%s' AND year='%s' AND month='%s' AND day='%s' AND grib_file='%s'",
                         latitude, longitude, year, month, day, grib_file);

                MYSQL *conn = mysql_init(NULL);
                if (mysql_real_connect(conn, "localhost", "root", "password", "database_name", 0, NULL, 0) == NULL) {
                    fprintf(stderr, "MySQL connection failed: %s\n", mysql_error(conn));
                    return -1;
                }

                if (mysql_query(conn, query)) {
                    fprintf(stderr, "MySQL query failed: %s\n", mysql_error(conn));
                    lws_write(wsi, "Internal Server Error", 20, LWS_WRITE_TEXT);
                } else {
                    MYSQL_RES *result = mysql_store_result(conn);
                    if (result) {
                        MYSQL_ROW row = mysql_fetch_row(result);
                        if (row && row[0]) {
                            char response[256];
                            snprintf(response, sizeof(response), "{\"max_temperature\": \"%s\"}", row[0]);
                            lws_write(wsi, response, strlen(response), LWS_WRITE_TEXT);
                        } else {
                            lws_write(wsi, "{\"error\":\"No data found.\"}", 29, LWS_WRITE_TEXT);
                        }
                        mysql_free_result(result);
                    } else {
                        fprintf(stderr, "MySQL fetch result failed: %s\n", mysql_error(conn));
                        lws_write(wsi, "Internal Server Error", 20, LWS_WRITE_TEXT);
                    }
                }

                mysql_close(conn);
            }
            break;
        }

        case LWS_CALLBACK_HTTP_DROP_CONNECTION:
            break;

        default:
            return -1;
    }
    return 0;
}

static struct lws_protocols protocols[] = {
    { "http-only", callback_http, sizeof(request_buffer), 4096 },
    { NULL, NULL, 0, 0 }
};

int main() {
    struct lws_context_creation_info info;
    memset(&info, 0, sizeof(info));

    info.port = PORT;
    info.address = ADDRESS;
    info.protocols = protocols;
    info.gid = -1;
    info.uid = -1;

    struct lws_context *context = lws_create_context(&info);
    if (!context) {
        fprintf(stderr, "Failed to create WebSocket context.\n");
        return -1;
    }

    while (1) {
        lws_service(context, 1000 / 50);
    }

    lws_context_destroy(context);
    return 0;
}


Note: This code assumes that you have `libwebsockets` and `mysqlclient` installed on your system. You might need to link against these libraries when compiling the program using a command like:


gcc -o web_app main.c -lwebsockets -lmysqlclient