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
    if (0 != strcmp(method, "GET"))
        return MHD_NO; // We only accept GET requests

    if (strcmp(url, "/api/temperature_for_location") == 0) {
        char *longitude = getenv("LONGITUDE");
        char *year = getenv("YEAR");
        char *month = getenv("MONTH");
        char *day = getenv("DAY");
        char *grib_file = getenv("GRIB_FILE");

        if (!longitude || !year || !month || !day || !grib_file) {
            const char *response = "Missing required parameters";
            struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, resp);
            MHD_destroy_response(resp);
            return ret;
        }

        MYSQL *conn;
        conn = mysql_init(NULL);

        if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
            const char *response = "Database connection failed";
            struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, resp);
            MHD_destroy_response(resp);
            mysql_close(conn);
            return ret;
        }

        char query[512];
        snprintf(query, sizeof(query),
                 "SELECT MAX(temperature) FROM temperature_data WHERE longitude='%s' AND year=%s AND month=%s AND day=%s AND grib_file='%s'",
                 longitude, year, month, day, grib_file);

        if (mysql_query(conn, query)) {
            const char *response = "Query execution failed";
            struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, resp);
            MHD_destroy_response(resp);
            mysql_close(conn);
            return ret;
        }

        MYSQL_RES *result = mysql_store_result(conn);

        if (!result) {
            const char *response = "Failed to retrieve query results";
            struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, resp);
            MHD_destroy_response(resp);
            mysql_close(conn);
            return ret;
        }

        MYSQL_ROW row = mysql_fetch_row(result);

        if (!row) {
            const char *response = "No data found";
            struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, resp);
            MHD_destroy_response(resp);
            mysql_free_result(result);
            mysql_close(conn);
            return ret;
        }

        const char *temperature = row[0];
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(temperature), (void *)temperature, MHD_RESPMEM_PERSISTENT);

        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        mysql_free_result(result);
        mysql_close(conn);
        return ret;
    }

    const char *response = "Not Found";
    struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, resp);
    MHD_destroy_response(resp);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_INTERNAL_POLLING_THREAD, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);

    if (NULL == daemon) return 1;

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}