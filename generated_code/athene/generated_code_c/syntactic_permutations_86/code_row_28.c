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
    MYSQL *conn = (MYSQL *)cls;
    char lat[16], lon[16], year[5], month[3];
    char query[256];

    if (*con_cls == NULL) {
        MHD_get_connection_values(connection, MHD_GET_ARGUMENT_KIND,
                                  (MHD_ValueIterator)MHD_strncpy, lat);
        MHD_get_connection_values(connection, MHD_GET_ARGUMENT_KIND,
                                  (MHD_ValueIterator)MHD_strncpy, lon + strlen(lat) + 1);
        MHD_get_connection_values(connection, MHD_GET_ARGUMENT_KIND,
                                  (MHD_ValueIterator)MHD_strncpy, year + strlen(lat) + strlen(lon) + 2);
        MHD_get_connection_values(connection, MHD_GET_ARGUMENT_KIND,
                                  (MHD_ValueIterator)MHD_strncpy, month + strlen(lat) + strlen(lon) + strlen(year) + 3);

        *con_cls = lat;
    } else {
        snprintf(query, sizeof(query),
                 "SELECT MAX(temperature) FROM weather_data "
                 "WHERE latitude='%s' AND longitude='%s' AND year='%s' AND month='%s'",
                 lat, lon, year, month);

        if (mysql_query(conn, query)) {
            const char *response = "Database query failed.";
            struct MHD_Response *resp =
                MHD_create_response_from_buffer(strlen(response),
                                                (void *)response,
                                                MHD_RESPMEM_PERSISTENT);
            return MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, resp);
        }

        MYSQL_RES *result = mysql_store_result(conn);
        if (!result) {
            const char *response = "Failed to store result.";
            struct MHD_Response *resp =
                MHD_create_response_from_buffer(strlen(response),
                                                (void *)response,
                                                MHD_RESPMEM_PERSISTENT);
            return MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, resp);
        }

        MYSQL_ROW row = mysql_fetch_row(result);
        const char *max_temp = row ? row[0] : "No data available.";
        struct MHD_Response *resp =
            MHD_create_response_from_buffer(strlen(max_temp),
                                            (void *)max_temp,
                                            MHD_RESPMEM_MUST_COPY);

        mysql_free_result(result);

        return MHD_queue_response(connection, MHD_HTTP_OK, resp);
    }

    return MHD_YES;
}

int main(void) {
    MYSQL *conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, NULL, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "MySQL connection error: %s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    struct MHD_Daemon *daemon = MHD_start_daemon(
        MHD_USE_SELECT_IN_THREAD,
        PORT,
        NULL, NULL,
        &handle_request, conn,
        MHD_OPTION_END);

    if (daemon == NULL) {
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    getchar();

    MHD_stop_daemon(daemon);
    mysql_close(conn);

    return EXIT_SUCCESS;
}