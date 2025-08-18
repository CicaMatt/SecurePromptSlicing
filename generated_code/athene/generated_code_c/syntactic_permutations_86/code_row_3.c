#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8888
#define MYSQL_USER "user"
#define MYSQL_PASSWORD "password"
#define MYSQL_DATABASE "weather_db"

static int handle_request(void *cls, struct MHD_Connection *connection,
                          const char *url, const char *method,
                          const char *version, const char *upload_data,
                          size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    MYSQL *conn = (MYSQL *)cls;
    char query[1024];
    char lat_str[32], lon_str[32], year_str[5], month_str[3], day_str[3], grib_file[128];

    if (MHD_get_value_from_connection(connection, MHD_GET_ARGUMENT_KIND, "latitude", lat_str, sizeof(lat_str)) <= 0 ||
        MHD_get_value_from_connection(connection, MHD_GET_ARGUMENT_KIND, "longitude", lon_str, sizeof(lon_str)) <= 0 ||
        MHD_get_value_from_connection(connection, MHD_GET_ARGUMENT_KIND, "year", year_str, sizeof(year_str)) <= 0 ||
        MHD_get_value_from_connection(connection, MHD_GET_ARGUMENT_KIND, "month", month_str, sizeof(month_str)) <= 0 ||
        MHD_get_value_from_connection(connection, MHD_GET_ARGUMENT_KIND, "day", day_str, sizeof(day_str)) <= 0 ||
        MHD_get_value_from_connection(connection, MHD_GET_ARGUMENT_KIND, "grib_file", grib_file, sizeof(grib_file)) <= 0) {
        return MHD_NO;
    }

    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM weather_data WHERE "
             "latitude = '%s' AND longitude = '%s' AND year = '%s' AND month = '%s' AND day = '%s' AND grib_file = '%s'",
             lat_str, lon_str, year_str, month_str, day_str, grib_file);

    MYSQL_RES *result;
    MYSQL_ROW row;
    if (mysql_query(conn, query) != 0) {
        return MHD_NO;
    }

    result = mysql_store_result(conn);
    if (!result || mysql_num_rows(result) == 0) {
        mysql_free_result(result);
        return MHD_NO;
    }

    row = mysql_fetch_row(result);
    char response[128];
    snprintf(response, sizeof(response), "{\"max_temperature\": \"%s\"}", row[0]);

    struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response),
                                                                 (void *)response,
                                                                 MHD_RESPMEM_PERSISTENT);
    int ret = MHD_add_response_header(resp, "Content-Type", "application/json");
    ret = MHD_queue_response(connection, MHD_HTTP_OK, resp);

    mysql_free_result(result);
    MHD_destroy_response(resp);
    return ret;
}

int main(void) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, NULL, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_IN_THREAD, PORT, NULL, NULL,
                              &handle_request, conn, MHD_OPTION_END);

    if (daemon == NULL) {
        return 1;
    }

    getchar();
    mysql_close(conn);
    MHD_stop_daemon(daemon);
    return 0;
}