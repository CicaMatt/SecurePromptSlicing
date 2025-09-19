#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <libmicrohttpd.h>

#define PORT 8888

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls) {
    if (0 != strcmp(method, "GET")) {
        return MHD_NO; // only handle GET requests
    }

    struct MHD_Response *response;
    int ret;

    // Parse request URL
    const char *query_string = strchr(url, '?') + 1;
    if (!query_string || strlen(query_string) == 0) {
        response = MHD_create_response_from_buffer(strlen("Invalid Request"),
                                                   (void *) "Invalid Request", MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        MHD_destroy_response(response);
        return ret;
    }

    // Extract parameters from query string
    char latitude[16], longitude[16], year[5], month[3], day[3], grib_file[256];
    if (sscanf(query_string, "latitude=%15s&longitude=%15s&year=%4s&month=%2s&day=%2s&grib_file=%255s",
               latitude, longitude, year, month, day, grib_file) != 6) {
        response = MHD_create_response_from_buffer(strlen("Invalid Request"),
                                                   (void *) "Invalid Request", MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        MHD_destroy_response(response);
        return ret;
    }

    // Connect to MySQL database
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "username", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        response = MHD_create_response_from_buffer(strlen("Database connection failed"),
                                                   (void *) "Database connection failed",
                                                   MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
        MHD_destroy_response(response);
        mysql_close(conn);
        return ret;
    }

    // Prepare SQL query
    char sql[512];
    snprintf(sql, sizeof(sql), "SELECT MAX(temperature) FROM weather_data "
                               "WHERE latitude = '%s' AND longitude = '%s' AND year = '%s' "
                               "AND month = '%s' AND day = '%s' AND grib_file = '%s'",
             latitude, longitude, year, month, day, grib_file);

    // Execute query
    if (mysql_query(conn, sql)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        response = MHD_create_response_from_buffer(strlen("Query execution failed"),
                                                   (void *) "Query execution failed",
                                                   MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
        MHD_destroy_response(response);
    } else {
        MYSQL_RES *result = mysql_store_result(conn);
        if (!result) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            response = MHD_create_response_from_buffer(strlen("Failed to retrieve results"),
                                                       (void *) "Failed to retrieve results",
                                                       MHD_RESPMEM_PERSISTENT);
            ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
        } else {
            MYSQL_ROW row = mysql_fetch_row(result);
            if (row && row[0]) {
                char *response_text = malloc(strlen("Max Temperature: ") + strlen(row[0]) + 1);
                snprintf(response_text, strlen("Max Temperature: ") + strlen(row[0]) + 1,
                         "Max Temperature: %s", row[0]);
                response = MHD_create_response_from_buffer(strlen(response_text),
                                                           (void *) response_text, MHD_RESPMEM_MUST_COPY);
                free(response_text);
            } else {
                response = MHD_create_response_from_buffer(strlen("No data found"),
                                                           (void *) "No data found",
                                                           MHD_RESPMEM_PERSISTENT);
            }
            mysql_free_result(result);
        }
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
    }

    mysql_close(conn);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);

    if (NULL == daemon) return 1;

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}