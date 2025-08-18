#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8888

MYSQL *conn;

int handle_request(void *cls, struct MHD_Connection *connection,
                   const char *url, const char *method,
                   const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *latitude_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude");
    const char *longitude_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "longitude");
    const char *year_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "year");
    const char *month_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "month");
    const char *day_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "day");
    const char *grib_file = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "grib_file");

    if (!latitude_str || !longitude_str || !year_str || !month_str || !day_str || !grib_file) {
        return MHD_NO;
    }

    double latitude = atof(latitude_str);
    double longitude = atof(longitude_str);
    int year = atoi(year_str);
    int month = atoi(month_str);
    int day = atoi(day_str);

    char query[512];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM weather_data WHERE latitude=%.6f AND longitude=%.6f AND YEAR(date)=%d AND MONTH(date)=%d AND DAY(date)=%d AND grib_file='%s'",
             latitude, longitude, year, month, day, grib_file);

    MYSQL_RES *result;
    MYSQL_ROW row;

    mysql_real_query(conn, query, strlen(query));
    result = mysql_store_result(conn);

    const char *response = "No data found";
    if (mysql_num_rows(result) > 0) {
        row = mysql_fetch_row(result);
        response = row[0] ? row[0] : "No temperature data";
    }

    mysql_free_result(result);

    int ret;
    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main() {
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "username", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                                   &handle_request, NULL, MHD_OPTION_END);
    if (NULL == daemon) {
        return 1;
    }

    printf("Server started on port %d\n", PORT);

    getchar(); // Wait for keypress

    mysql_close(conn);
    MHD_stop_daemon(daemon);

    return 0;
}