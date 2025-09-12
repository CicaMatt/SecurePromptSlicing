#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8080
#define MYSQL_HOST "localhost"
#define MYSQL_USER "root"
#define MYSQL_PASS "password"
#define MYSQL_DB "weather"

static int handle_request(void *cls, struct MHD_Connection *connection,
                          const char *url, const char *method,
                          const char *version, const char *upload_data,
                          size_t *upload_data_size, void **con_cls) {
    MYSQL *conn = (MYSQL *) cls;
    const char *query_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "query");
    if (!query_str || strcmp(method, MHD_HTTP_METHOD_GET) != 0) {
        return MHD_NO;
    }

    double lat, lon;
    int year, month, day;
    char grib_file[256];
    sscanf(query_str, "lat=%lf&lon=%lf&year=%d&month=%d&day=%d&grib_file=%s", &lat, &lon, &year, &month, &day, grib_file);

    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[512];
    snprintf(query, 512,
             "SELECT MAX(temperature) FROM weather_data WHERE latitude = %lf AND longitude = %lf AND year = %d AND month = %d AND day = %d AND grib_file = '%s'",
             lat, lon, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        return MHD_NO;
    }

    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);
    char *max_temp_str = row ? strdup(row[0]) : strdup("null");

    struct MHD_Response *response;
    response = MHD_create_response_from_buffer(strlen(max_temp_str), (void *) max_temp_str, MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    free(max_temp_str);
    mysql_free_result(res);
    return ret;
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_DB, 0, NULL, 0)) {
        fprintf(stderr, "MySQL connection failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_IN_THREAD, PORT, NULL, NULL,
                                                  &handle_request, conn, MHD_OPTION_END);
    if (!daemon) {
        fprintf(stderr, "Failed to start daemon\n");
        mysql_close(conn);
        return 1;
    }

    getchar();
    MHD_stop_daemon(daemon);
    mysql_close(conn);
    return 0;
}