#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8888

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **ptr) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    int ret;
    struct MHD_Response *response;
    MYSQL mysql;
    MYSQL_RES *result;
    MYSQL_ROW row;
    char query[512];

    // Initialize MySQL connection
    mysql_init(&mysql);
    if (!mysql_real_connect(&mysql, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&mysql));
        response = MHD_create_response_from_buffer(strlen("Database connection failed"), (void *) "Database connection failed",
                                                   MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
        MHD_destroy_response(response);
        return ret;
    }

    // Parse POST data
    if (*upload_data_size != 0) {
        char latitude[10], longitude[10], year[5], month[3], day[3], grib_file[50];
        sscanf(upload_data, "latitude=%[^;];longitude=%[^;];year=%[^;];month=%[^;];day=%[^;];grib_file=%s",
               latitude, longitude, year, month, day, grib_file);

        // Prepare SQL query
        snprintf(query, sizeof(query),
                 "SELECT MAX(temperature) FROM temperature_data WHERE latitude = '%s' AND "
                 "longitude = '%s' AND year = '%s' AND month = '%s' AND day = '%s' AND grib_file = '%s'",
                 latitude, longitude, year, month, day, grib_file);

        // Execute query
        if (mysql_query(&mysql, query)) {
            fprintf(stderr, "%s\n", mysql_error(&mysql));
            response = MHD_create_response_from_buffer(strlen("Query execution failed"), (void *) "Query execution failed",
                                                       MHD_RESPMEM_PERSISTENT);
            ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
            MHD_destroy_response(response);
        } else {
            result = mysql_store_result(&mysql);
            if ((row = mysql_fetch_row(result))) {
                char *response_str = malloc(100);
                snprintf(response_str, 100, "Max Temperature: %s", row[0]);
                response = MHD_create_response_from_buffer(strlen(response_str), (void *) response_str,
                                                           MHD_RESPMEM_MUST_FREE);
                ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
                MHD_destroy_response(response);
            } else {
                response = MHD_create_response_from_buffer(strlen("No data found"), (void *) "No data found",
                                                           MHD_RESPMEM_PERSISTENT);
                ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
                MHD_destroy_response(response);
            }
        }

        mysql_free_result(result);
    } else {
        response = MHD_create_response_from_buffer(strlen("Invalid request"), (void *) "Invalid request",
                                                   MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        MHD_destroy_response(response);
    }

    mysql_close(&mysql);

    *upload_data_size = 0;
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar(); // Wait for Enter key press

    MHD_stop_daemon(daemon);
    return 0;
}