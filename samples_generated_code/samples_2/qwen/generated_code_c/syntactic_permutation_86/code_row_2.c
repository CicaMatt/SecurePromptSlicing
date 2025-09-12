#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <mysql/mysql.h>

#define PORT 8080

MYSQL *conn;

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strstr(url, "/api/temperature_for_location?") != url)
        return MHD_NO;

    const char* query_string = strchr(url, '?') + 1;
    char latitude[20], longitude[20], year[5], month[3], day[3], grib_file[100];
    sscanf(query_string, "latitude=%[^&]&longitude=%[^&]&year=%[^&]&month=%[^&]&day=%[^&]&grib_file=%s",
           latitude, longitude, year, month, day, grib_file);

    char query[256];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM weather_data WHERE "
             "latitude=%.4f AND longitude=%.4f AND YEAR(date)=%d AND MONTH(date)=%d AND DAY(date)=%d AND grib_file='%s'",
             atof(latitude), atof(longitude), atoi(year), atoi(month), atoi(day), grib_file);

    if (mysql_query(conn, query)) {
        const char *error_response = "Failed to execute query";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_response),
                                                                        (void *) error_response,
                                                                        MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
        MHD_destroy_response(response);
        return ret;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        const char *error_response = "Failed to store result";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_response),
                                                                        (void *) error_response,
                                                                        MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
        MHD_destroy_response(response);
        return ret;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    const char *response_str = row ? row[0] : "No data found";
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(response_str),
                                                                    (void *) response_str,
                                                                    MHD_RESPMEM_PERSISTENT);
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

    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);

    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    mysql_close(conn);
    return 0;
}