#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8080

MYSQL *conn;

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strncmp(url, "/api/temperature_for_location", strlen("/api/temperature_for_location")) != 0)
        return MHD_NO;

    const char *latitude = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude");
    const char *longitude = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "longitude");
    const char *year = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "year");
    const char *month = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "month");

    if (!latitude || !longitude || !year || !month)
        return MHD_NO;

    char query[512];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM weather_data WHERE latitude=%s AND longitude=%s AND YEAR(date)=%s AND MONTH(date)=%s",
             latitude, longitude, year, month);

    if (mysql_query(conn, query)) {
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(mysql_error(conn)),
                                                                         (void *) mysql_error(conn),
                                                                         MHD_RESPMEM_MUST_FREE);
        return MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(mysql_error(conn)),
                                                                         (void *) mysql_error(conn),
                                                                         MHD_RESPMEM_MUST_FREE);
        return MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
    }

    MYSQL_ROW row;
    const char *temperature = "No data found";
    if ((row = mysql_fetch_row(result))) {
        temperature = row[0] ? row[0] : "No data found";
    }

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(temperature),
                                                                     (void *) temperature,
                                                                     MHD_RESPMEM_PERSISTENT);
    mysql_free_result(result);

    return MHD_queue_response(connection, MHD_HTTP_OK, response);
}

int main() {
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (!daemon)
        return 1;

    getchar();

    mysql_close(conn);

    MHD_stop_daemon(daemon);
    return 0;
}