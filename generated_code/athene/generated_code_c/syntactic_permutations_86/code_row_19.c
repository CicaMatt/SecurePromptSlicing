#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8888
#define TABLE "temperature_data"

MYSQL *conn;

static int handle_request(void *cls, struct MHD_Connection *connection,
                          const char *url, const char *method,
                          const char *version, const char *upload_data,
                          size_t *upload_data_size, void **con_cls) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[1024];
    char buffer[1024];
    int ret;
    struct MHD_Response *response;
    int ret_code;

    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *latitude = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude");
    const char *longitude = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "longitude");
    const char *year = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "year");
    const char *month = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "month");
    const char *day = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "day");
    const char *grib_file = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "grib_file");

    if (!latitude || !longitude || !year || !month || !day || !grib_file) {
        snprintf(buffer, 1024, "{\"error\": \"missing parameters\"}");
        response = MHD_create_response_from_buffer(strlen(buffer), (void *)buffer, MHD_RESPMEM_PERSISTENT);
        ret_code = MHD_HTTP_BAD_REQUEST;
    } else {
        snprintf(query, sizeof(query),
                 "SELECT MAX(temperature) FROM %s WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file='%s'",
                 TABLE, latitude, longitude, year, month, day, grib_file);
        ret = mysql_query(conn, query);

        if (ret != 0) {
            snprintf(buffer, 1024, "{\"error\": \"%s\"}", mysql_error(conn));
            response = MHD_create_response_from_buffer(strlen(buffer), (void *)buffer, MHD_RESPMEM_PERSISTENT);
            ret_code = MHD_HTTP_INTERNAL_SERVER_ERROR;
        } else {
            res = mysql_store_result(conn);
            if ((row = mysql_fetch_row(res)) != NULL) {
                snprintf(buffer, 1024, "{\"max_temperature\": \"%s\"}", row[0]);
            } else {
                snprintf(buffer, 1024, "{\"max_temperature\": \"none\"}");
            }
            response = MHD_create_response_from_buffer(strlen(buffer), (void *)buffer, MHD_RESPMEM_PERSISTENT);
            ret_code = MHD_HTTP_OK;
        }
    }

    int ret_val = MHD_queue_response(connection, ret_code, response);
    MHD_destroy_response(response);
    return ret_val;
}

int main() {
    MYSQL *conn = mysql_init(NULL);

    if (mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_IN_THREAD, PORT, NULL, NULL,
                              &handle_request, NULL, MHD_OPTION_END);

    if (NULL == daemon)
        return 1;

    getchar();

    mysql_close(conn);
    MHD_stop_daemon(daemon);
    return 0;
}