#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8080
#define MYSQL_USER "user"
#define MYSQL_PASSWORD "password"
#define MYSQL_DATABASE "db_name"

static int handle_request(void *cls, struct MHD_Connection *connection,
                          const char *url, const char *method,
                          const char *version, const char *upload_data,
                          size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, NULL, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        const char *response = "Database connection failed";
        struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, resp);
    }

    char lat[10], lon[10], year[5], month[3], day[3], grib_file[256];
    if (MHD_get_value_from_connection(connection, MHD_GET_ARGUMENT_KIND, "latitude", lat) == NULL ||
        MHD_get_value_from_connection(connection, MHD_GET_ARGUMENT_KIND, "longitude", lon) == NULL ||
        MHD_get_value_from_connection(connection, MHD_GET_ARGUMENT_KIND, "year", year) == NULL ||
        MHD_get_value_from_connection(connection, MHD_GET_ARGUMENT_KIND, "month", month) == NULL ||
        MHD_get_value_from_connection(connection, MHD_GET_ARGUMENT_KIND, "day", day) == NULL ||
        MHD_get_value_from_connection(connection, MHD_GET_ARGUMENT_KIND, "grib_file", grib_file) == NULL) {
        const char *response = "Missing required parameters";
        struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, resp);
    }

    char query[512];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM weather_data WHERE latitude = '%s' AND longitude = '%s' AND year = '%s' AND month = '%s' AND day = '%s' AND grib_file = '%s'",
             lat, lon, year, month, day, grib_file);

    MYSQL_RES *result;
    if (mysql_query(conn, query) != 0) {
        const char *response = "Query execution failed";
        struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, resp);
    }

    result = mysql_store_result(conn);
    MYSQL_ROW row;
    if ((row = mysql_fetch_row(result)) != NULL) {
        char *max_temp = (char *)malloc(strlen(row[0]) + 1);
        strcpy(max_temp, row[0]);
        struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(max_temp), max_temp, MHD_RESPMEM_MUST_COPY);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, resp);
        free(max_temp);
        return ret;
    } else {
        const char *response = "No data found";
        struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, resp);
    }

    mysql_free_result(result);
    mysql_close(conn);

    return MHD_YES;
}

int main(void) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_IN_THREAD, PORT, NULL, NULL,
                              &handle_request, NULL, MHD_OPTION_END);
    if (daemon == NULL)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}