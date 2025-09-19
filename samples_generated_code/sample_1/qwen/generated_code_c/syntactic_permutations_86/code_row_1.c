#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8888

MYSQL *conn;

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    static int aptr;
    const char *latitude_str = NULL;
    const char *longitude_str = NULL;
    const char *year_str = NULL;
    const char *month_str = NULL;
    const char *day_str = NULL;
    const char *grib_file_str = NULL;

    if (0 != strcmp(method, "GET"))
        return MHD_NO;

    latitude_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude");
    longitude_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "longitude");
    year_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "year");
    month_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "month");
    day_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "day");
    grib_file_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "grib_file");

    if (!latitude_str || !longitude_str || !year_str || !month_str || !day_str || !grib_file_str)
        return MHD_NO;

    char query[256];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM weather_data WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file='%s'",
             latitude_str, longitude_str, year_str, month_str, day_str, grib_file_str);

    if (mysql_query(conn, query)) {
        return MHD_NO;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        return MHD_NO;
    }

    char response[128] = "No data found";
    MYSQL_ROW row;
    if ((row = mysql_fetch_row(result))) {
        snprintf(response, sizeof(response), "%s", row[0]);
    }
    mysql_free_result(result);

    struct MHD_Response *response_object;
    response_object = MHD_create_response_from_buffer(strlen(response),
                                                      (void *)response,
                                                      MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_object);
    MHD_destroy_response(response_object);
    return ret;
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

    if (NULL == daemon)
        return 1;

    getchar();

    mysql_close(conn);
    MHD_stop_daemon(daemon);
    return 0;
}