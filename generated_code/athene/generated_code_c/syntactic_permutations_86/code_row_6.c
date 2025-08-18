#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8080
#define MYSQL_USER "user"
#define MYSQL_PASSWORD "password"
#define MYSQL_DATABASE "weather_db"

static int handle_request(void *cls, struct MHD_Connection *connection,
                          const char *url, const char *method,
                          const char *version, const char *upload_data,
                          size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    MYSQL *conn = (MYSQL *)cls;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[1024];
    char response[256];

    const char *latitude = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude");
    const char *longitude = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "longitude");
    const char *year = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "year");
    const char *month = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "month");
    const char *day = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "day");
    const char *grib_file = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "grib_file");

    if (!latitude || !longitude || !year || !month || !day || !grib_file) {
        snprintf(response, sizeof(response), "{\"error\": \"Missing parameters\"}");
        struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response),
                                                                     (void *)response,
                                                                     MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, resp);
    }

    snprintf(query, sizeof(query), "SELECT MAX(temperature) FROM weather_data WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file='%s'",
             latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        snprintf(response, sizeof(response), "{\"error\": \"%s\"}", mysql_error(conn));
        struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response),
                                                                     (void *)response,
                                                                     MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, resp);
    }

    res = mysql_store_result(conn);
    if (res) {
        row = mysql_fetch_row(res);
        if (row && row[0]) {
            snprintf(response, sizeof(response), "{\"max_temperature\": \"%s\"}", row[0]);
        } else {
            snprintf(response, sizeof(response), "{\"max_temperature\": \"null\"}");
        }
        mysql_free_result(res);
    } else {
        snprintf(response, sizeof(response), "{\"error\": \"No result returned\"}");
    }

    struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response),
                                                                 (void *)response,
                                                                 MHD_RESPMEM_PERSISTENT);
    return MHD_queue_response(connection, MHD_HTTP_OK, resp);
}

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, NULL, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_IN_THREAD, PORT, NULL, NULL,
                              &handle_request, conn, MHD_OPTION_END);

    if (daemon == NULL) {
        fprintf(stderr, "MHD_start_daemon failed\n");
        mysql_close(conn);
        return 1;
    }

    getchar();
    MHD_stop_daemon(daemon);
    mysql_close(conn);
    return 0;
}