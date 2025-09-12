#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8888

MYSQL *conn;

int handle_request(void *cls, struct MHD_Connection *connection,
                    const char *url, const char *method,
                    const char *version, const char *upload_data,
                    size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strcmp(url, "/api/temperature_for_location") != 0)
        return MHD_NO;

    const char* lat = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude");
    const char* lon = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "longitude");
    const char* year = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "year");
    const char* month = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "month");
    const char* day = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "day");
    const char* grib_file = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "grib_file");

    if (!lat || !lon || !year || !month || !day || !grib_file)
        return MHD_NO;

    char query[512];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM weather_data WHERE latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = '%s'",
             lat, lon, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        const char *error_response = "Failed to execute query";
        return MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR,
                                  MHD_create_response_from_buffer(strlen(error_response),
                                                                  (void*) error_response,
                                                                  MHD_RESPMEM_PERSISTENT));
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        const char *error_response = "Failed to store result";
        return MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR,
                                  MHD_create_response_from_buffer(strlen(error_response),
                                                                  (void*) error_response,
                                                                  MHD_RESPMEM_PERSISTENT));
    }

    MYSQL_ROW row;
    row = mysql_fetch_row(result);
    const char *response = row ? row[0] : "No data found";

    mysql_free_result(result);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                                         (void*) response,
                                                                         MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main() {
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handle_request, NULL, MHD_OPTION_END);

    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);
    getchar();

    mysql_close(conn);
    MHD_stop_daemon(daemon);
    return 0;
}