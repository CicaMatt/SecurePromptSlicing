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
    MYSQL_RES *res;
    MYSQL_ROW row;
    struct MHD_Response *response;
    int ret;

    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    char *query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, NULL);
    char latitude[16], longitude[16], year[5], month[3], day[3], grib_file[256];
    sscanf(query_string, "latitude=%[^&]&longitude=%[^&]&year=%[^&]&month=%[^&]&day=%[^&]&grib_file=%s",
           latitude, longitude, year, month, day, grib_file);

    char query[1024];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM temperatures "
             "WHERE latitude = '%s' AND longitude = '%s' AND year = '%s' AND month = '%s' AND day = '%s' AND grib_file = '%s'",
             latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query) != 0) {
        const char *error_message = mysql_error(conn);
        response = MHD_create_response_from_buffer(strlen(error_message), (void *) error_message, MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
    }

    res = mysql_store_result(conn);
    if ((row = mysql_fetch_row(res)) != NULL) {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "{\"max_temperature\": \"%s\"}", row[0]);
        response = MHD_create_response_from_buffer(strlen(buffer), (void *) buffer, MHD_RESPMEM_PERSISTENT);
    } else {
        const char *no_data_message = "{\"max_temperature\": \"No data found\"}";
        response = MHD_create_response_from_buffer(strlen(no_data_message), (void *) no_data_message, MHD_RESPMEM_PERSISTENT);
    }

    mysql_free_result(res);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, NULL, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "MySQL connection error: %s\n", mysql_error(conn));
        exit(1);
    }

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_IN_THREAD, PORT, NULL, NULL,
                                                 &handle_request, conn, MHD_OPTION_END);

    if (daemon == NULL) {
        fprintf(stderr, "Failed to start daemon\n");
        mysql_close(conn);
        exit(1);
    }

    while (1)
        pause();

    MHD_stop_daemon(daemon);
    mysql_close(conn);

    return 0;
}