#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8888

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strcmp(url, "/api/temperature_for_location") != 0)
        return MHD_NO;

    const char *latitude = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude");
    const char *longitude = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "longitude");
    const char *year = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "year");
    const char *month = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "month");
    const char *day = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "day");
    const char *grib_file = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "grib_file");

    if (!latitude || !longitude || !year || !month || !day || !grib_file)
        return MHD_NO;

    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return MHD_NO;
    }

    char query[1024];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM temperature_data WHERE latitude = %f AND longitude = %f AND YEAR(date) = %d AND MONTH(date) = %d AND DAY(date) = %d AND grib_file = '%s'",
             atof(latitude), atof(longitude), atoi(year), atoi(month), atoi(day), grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return MHD_NO;
    }

    res = mysql_use_result(conn);

    row = mysql_fetch_row(res);
    const char *response = row ? row[0] : "No data found";

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void *) response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);

    mysql_free_result(res);
    mysql_close(conn);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar(); // Wait for keypress

    MHD_stop_daemon(daemon);
    return 0;
}