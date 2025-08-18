#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8080

MYSQL *conn;
char response[128];

int send_response(void *cls, struct MHD_Connection *connection, const char *url, const char *method) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strcmp(url, "/api/temperature_for_location") == 0) {
        const char *latitude = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude");
        const char *longitude = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "longitude");
        const char *date = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "date");

        if (latitude && longitude && date) {
            char query[256];
            snprintf(query, sizeof(query), "SELECT temperature FROM weather_data WHERE latitude=%s AND longitude=%s AND date='%s'", latitude, longitude, date);

            if (mysql_query(conn, query)) {
                snprintf(response, sizeof(response), "{\"error\": \"%s\"}", mysql_error(conn));
            } else {
                MYSQL_RES *result = mysql_store_result(conn);
                if (result) {
                    MYSQL_ROW row = mysql_fetch_row(result);
                    if (row && row[0]) {
                        snprintf(response, sizeof(response), "{\"temperature\": %s}", row[0]);
                    } else {
                        strcpy(response, "{\"error\": \"No data found\"}");
                    }
                    mysql_free_result(result);
                } else {
                    snprintf(response, sizeof(response), "{\"error\": \"%s\"}", mysql_error(conn));
                }
            }
        } else {
            strcpy(response, "{\"error\": \"Missing parameters\"}");
        }

        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_MUST_COPY);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
        MHD_destroy_response(mhd_response);

        return ret;
    }

    return MHD_NO;
}

int main() {
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "username", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL, &send_response, NULL, MHD_OPTION_END);
    if (!daemon) {
        return 1;
    }

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    mysql_close(conn);

    return 0;
}