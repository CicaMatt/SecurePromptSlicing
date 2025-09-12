#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8080

MYSQL *conn;

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/api/temperature_for_location") != 0)
        return MHD_NO;

    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char* latitude = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude");
    const char* longitude = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "longitude");
    const char* year = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "year");
    const char* month = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "month");
    const char* day = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "day");
    const char* grib_file = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "grib_file");

    if (!latitude || !longitude || !year || !month || !day || !grib_file)
        return MHD_NO;

    char query[512];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM temperature_data WHERE latitude = %s AND longitude = %s AND YEAR(date) = %s AND MONTH(date) = %s AND DAY(date) = %s AND grib_file = '%s'",
             latitude, longitude, year, month, day, grib_file);

    MYSQL_RES *result;
    MYSQL_ROW row;

    mysql_real_query(conn, query, strlen(query));
    result = mysql_store_result(conn);

    const char* response = "No data found";
    if (mysql_num_fields(result) > 0 && (row = mysql_fetch_row(result)) != NULL && row[0] != NULL)
        response = row[0];

    struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
    MHD_destroy_response(response_obj);
    mysql_free_result(result);

    return ret;
}

int main() {
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "127.0.0.1", "user", "password", "database_name", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL, &answer_to_connection, NULL,
                                                  MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    mysql_close(conn);
    MHD_stop_daemon(daemon);

    return 0;
}