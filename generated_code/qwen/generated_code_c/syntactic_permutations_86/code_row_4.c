#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8888

int handle_request(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/api/temperature_for_location") != 0 || strcmp(method, "GET") != 0)
        return MHD_NO;

    const char* latitude = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude");
    const char* longitude = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "longitude");
    const char* year = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "year");
    const char* month = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "month");
    const char* day = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "day");
    const char* grib_file = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "grib_file");

    if (!latitude || !longitude || !year || !month || !day || !grib_file)
        return MHD_NO;

    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0) == NULL) {
        const char* response = "{\"error\": \"Failed to connect to database\"}";
        return MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR,
                                  MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT));
    }

    char query[1024];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM temperatures WHERE latitude=%s AND longitude=%s AND YEAR(date)=%s AND MONTH(date)=%s AND DAY(date)=%s AND grib_file='%s'",
             latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        const char* response = "{\"error\": \"Failed to execute query\"}";
        mysql_close(conn);
        return MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR,
                                  MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT));
    }

    res = mysql_use_result(conn);

    char response[256] = "{\"temperature\": ";
    if ((row = mysql_fetch_row(res)) != NULL && row[0] != NULL) {
        strcat(response, row[0]);
    } else {
        strcat(response, "null");
    }
    strcat(response, "}");

    mysql_free_result(res);
    mysql_close(conn);

    struct MHD_Response *mhd_response;
    mhd_response = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handle_request, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}