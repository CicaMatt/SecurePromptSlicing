#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8888

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0 && strcmp(method, "POST") != 0) {
        return MHD_NO;
    }

    struct url_params params = {0};
    char response[1024];
    int ret;

    // Parse URL parameters
    if (*url_cls == NULL || strlen(url) < strlen("/api/temperature_for_location?")) {
        snprintf(response, sizeof(response), "Invalid request");
        ret = MHD_NO;
    } else {
        char *query_string = strchr(url, '?') + 1;
        sscanf(query_string,
               "latitude=%lf&longitude=%lf&year=%d&month=%d&day=%d&grib_file=%s",
               &params.latitude, &params.longitude, &params.year, &params.month,
               &params.day, params.grib_file);

        // Connect to MySQL
        MYSQL *conn = mysql_init(NULL);
        if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
            snprintf(response, sizeof(response), "Database connection failed: %s",
                     mysql_error(conn));
            ret = MHD_NO;
        } else {
            // Prepare and execute query
            char query[512];
            snprintf(query, sizeof(query),
                     "SELECT MAX(temperature) FROM temperature_data WHERE "
                     "latitude=%lf AND longitude=%lf AND year=%d AND month=%d AND day=%d AND grib_file='%s'",
                     params.latitude, params.longitude, params.year, params.month,
                     params.day, params.grib_file);

            if (mysql_query(conn, query)) {
                snprintf(response, sizeof(response), "Query failed: %s", mysql_error(conn));
                ret = MHD_NO;
            } else {
                MYSQL_RES *result = mysql_store_result(conn);
                if (result) {
                    MYSQL_ROW row = mysql_fetch_row(result);
                    snprintf(response, sizeof(response), "Max temperature: %s",
                             row ? row[0] : "No data");
                    mysql_free_result(result);
                    ret = MHD_YES;
                } else {
                    snprintf(response, sizeof(response), "Query failed to store result: %s", mysql_error(conn));
                    ret = MHD_NO;
                }
            }

            mysql_close(conn);
        }
    }

    struct MHD_Response *response_struct = MHD_create_response_from_buffer(strlen(response),
                                                                            (void *)response,
                                                                            MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response_struct);

    MHD_destroy_response(response_struct);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY | MHD_USE_INTERNAL_POLLING_THREAD,
                              PORT, NULL, NULL, &answer_to_connection, NULL,
                              MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server running on port %d\n", PORT);

    getchar(); // Wait for user to stop the server

    MHD_stop_daemon(daemon);

    return 0;
}
