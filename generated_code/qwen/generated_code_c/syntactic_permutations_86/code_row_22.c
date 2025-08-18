#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8888

MYSQL *conn;

int send_response(struct MHD_Connection *connection, const char *data) {
    int ret;
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(data), (void*) data, MHD_RESPMEM_PERSISTENT);
    if (!response)
        return MHD_NO;
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return send_response(connection, "Method not allowed");

    if (strcmp(url, "/api/temperature_for_location") != 0)
        return send_response(connection, "Not found");

    const char *latitude = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude");
    const char *longitude = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "longitude");
    const char *year = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "year");
    const char *month = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "month");
    const char *day = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "day");
    const char *grib_file = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "grib_file");

    if (!latitude || !longitude || !year || !month || !day || !grib_file)
        return send_response(connection, "Missing parameters");

    char query[1024];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM weather_data WHERE latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = '%s';",
             latitude, longitude, year, month, day, grib_file);

    MYSQL_RES *result;
    MYSQL_ROW row;

    if (mysql_query(conn, query)) {
        return send_response(connection, "Query failed");
    }

    result = mysql_store_result(conn);
    if (!result) {
        return send_response(connection, "No results found");
    }

    char response[128];
    row = mysql_fetch_row(result);
    if (row && row[0]) {
        snprintf(response, sizeof(response), "Max temperature: %s", row[0]);
    } else {
        strcpy(response, "No data available for the given parameters");
    }

    mysql_free_result(result);

    return send_response(connection, response);
}

int main(int argc, char **argv) {
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                                 &answer_to_connection, NULL, MHD_OPTION_END);

    if (NULL == daemon) {
        return 1;
    }

    printf("Server running on port %d\n", PORT);
    getchar();

    mysql_close(conn);
    MHD_stop_daemon(daemon);

    return 0;
}