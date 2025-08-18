#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8888

MYSQL *conn;

int query_temperature(void *cls, struct MHD_Connection *connection,
                    const char *url, const char *method,
                    const char *version, const char *upload_data,
                    size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *lat = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude");
    const char *lon = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "longitude");
    const char *year = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "year");
    const char *month = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "month");
    const char *day = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "day");
    const char *grib_file = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "grib_file");

    if (!lat || !lon || !year || !month || !day || !grib_file)
        return MHD_NO;

    char query[256];
    snprintf(query, sizeof(query), "SELECT MAX(temperature) FROM temperatures WHERE latitude=%.6f AND longitude=%.6f AND year=%d AND month=%d AND day=%d AND grib_file='%s'",
             atof(lat), atof(lon), atoi(year), atoi(month), atoi(day), grib_file);

    if (mysql_query(conn, query)) {
        return MHD_NO;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result)
        return MHD_NO;

    MYSQL_ROW row = mysql_fetch_row(result);
    const char *response = row ? row[0] : "No data found";

    int ret = MHD_queue_response(connection, MHD_HTTP_OK,
                                  MHD_create_response_from_buffer(strlen(response),
                                                                  (void *) response,
                                                                  MHD_RESPMEM_PERSISTENT));

    mysql_free_result(result);

    return ret;
}

int main() {
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &query_temperature, NULL, MHD_OPTION_END);

    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    mysql_close(conn);
    MHD_stop_daemon(daemon);
    return 0;
}