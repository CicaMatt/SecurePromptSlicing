#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8080
#define MYSQL_HOST "localhost"
#define MYSQL_USER "user"
#define MYSQL_PASS "pass"
#define MYSQL_DB "weather_db"

static int handle_request(void *cls, struct MHD_Connection *connection,
                          const char *url, const char *method,
                          const char *version, const char *upload_data,
                          size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    MYSQL *conn = (MYSQL *)cls;
    const char *query_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "query");
    if (!query_str)
        return MHD_NO;

    char lat[16], lon[16], year[5], month[3], day[3], grib_file[256];
    sscanf(query_str, "lat=%[^&]&lon=%[^&]&year=%[^&]&month=%[^&]&day=%[^&]&grib_file=%s",
           lat, lon, year, month, day, grib_file);

    char query[1024];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM weather_data WHERE "
             "latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = '%s'",
             lat, lon, year, month, day, grib_file);

    MYSQL_RES *result;
    if (mysql_query(conn, query)) {
        return MHD_NO;
    }

    result = mysql_store_result(conn);
    if (!result) {
        return MHD_NO;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    char response[64];
    if (row && row[0]) {
        snprintf(response, sizeof(response), "{\"max_temperature\": %s}", row[0]);
    } else {
        snprintf(response, sizeof(response), "{\"max_temperature\": null}");
    }

    struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response),
                                                                 (void *)response,
                                                                 MHD_RESPMEM_MUST_COPY);
    int ret = MHD_add_response_header(resp, "Content-Type", "application/json");
    ret |= MHD_queue_response(connection, MHD_HTTP_OK, resp);
    MHD_destroy_response(resp);

    mysql_free_result(result);
    return ret;
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_DB, 0, NULL, 0)) {
        fprintf(stderr, "MySQL connection failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_IN_THREAD, PORT, NULL, NULL,
                                                  &handle_request, conn, MHD_OPTION_END);
    if (!daemon) {
        fprintf(stderr, "Failed to start daemon\n");
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    getchar();
    MHD_stop_daemon(daemon);
    mysql_close(conn);
    return 0;
}