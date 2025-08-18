#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8080
#define MYSQL_USER "user"
#define MYSQL_PASSWORD "password"
#define MYSQL_DB "weather_db"

int handle_request(void *cls, struct MHD_Connection *connection,
                   const char *url, const char *method,
                   const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls) {
    MYSQL *conn = (MYSQL *)cls;
    if (0 != strcmp(method, "GET")) {
        return MHD_NO;
    }

    const char *query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude");
    double latitude = atof(query_string ? query_string : "");

    query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "longitude");
    double longitude = atof(query_string ? query_string : "");

    query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "year");
    int year = atoi(query_string ? query_string : "");

    query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "month");
    int month = atoi(query_string ? query_string : "");

    query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "day");
    int day = atoi(query_string ? query_string : "");

    query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "grib_file");
    const char *grib_file = query_string ? query_string : "";

    if (latitude == 0 && longitude == 0 && year == 0 && month == 0 && day == 0 && grib_file[0] == '\0') {
        return MHD_NO;
    }

    char sql_query[256];
    snprintf(sql_query, sizeof(sql_query),
             "SELECT MAX(temperature) FROM weather_data WHERE latitude = %.4f AND longitude = %.4f AND year = %d AND month = %d AND day = %d AND grib_file = '%s'",
             latitude, longitude, year, month, day, grib_file);

    MYSQL_RES *result;
    MYSQL_ROW row;

    if (mysql_query(conn, sql_query) != 0) {
        return MHD_NO;
    }

    result = mysql_store_result(conn);
    if (!result || mysql_num_rows(result) == 0) {
        return MHD_NO;
    }

    row = mysql_fetch_row(result);
    char *response_body = malloc(64);
    snprintf(response_body, 64, "{\"max_temperature\": \"%s\"}", row[0] ? row[0] : "null");

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(response_body),
                                                                     (void *)response_body,
                                                                     MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    free(response_body);

    mysql_free_result(result);
    return ret;
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", MYSQL_USER, MYSQL_PASSWORD, MYSQL_DB, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_IN_THREAD, PORT, NULL, NULL,
                               &handle_request, conn, MHD_OPTION_END);

    if (NULL == daemon) {
        return 1;
    }

    getchar();
    mysql_close(conn);
    MHD_stop_daemon(daemon);
    return 0;
}