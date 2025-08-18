#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8080

MYSQL *conn;

int handle_request(void *cls, struct MHD_Connection *connection,
                   const char *url, const char *method,
                   const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0 || strcmp(url, "/api/temperature_for_location") != 0)
        return MHD_NO;

    const char *latitude = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude");
    const char *longitude = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "longitude");
    const char *year = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "year");
    const char *day = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "day");
    const char *grib_file = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "grib_file");

    if (!latitude || !longitude || !year || !day || !grib_file)
        return MHD_NO;

    char query[256];
    snprintf(query, sizeof(query), "SELECT MAX(temperature) FROM weather_data WHERE latitude = %s AND longitude = %s AND year = %s AND day = %s AND grib_file = '%s'", latitude, longitude, year, day, grib_file);

    if (mysql_query(conn, query)) {
        const char *error_response = "Error executing query";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_response), (void*) error_response, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
        MHD_destroy_response(response);
        return ret;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        const char *error_response = "Error storing result";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_response), (void*) error_response, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
        MHD_destroy_response(response);
        return ret;
    }

    MYSQL_ROW row;
    char *response_message;
    if ((row = mysql_fetch_row(result))) {
        asprintf(&response_message, "Maximum Temperature: %s", row[0]);
    } else {
        response_message = strdup("No data found");
    }
    
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(response_message), (void*) response_message, MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    mysql_free_result(result);

    return ret;
}

int main() {
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                                 &handle_request, NULL, MHD_OPTION_END);

    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    mysql_close(conn);

    return 0;
}