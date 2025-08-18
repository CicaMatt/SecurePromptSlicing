#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8888

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                             const char *url, const char *method,
                             const char *version, const char *upload_data,
                             size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strstr(url, "/api/temperature_for_location?")) {
        const char *query = strchr(url, '?') + 1;
        char latitude[50], longitude[50], year[50], month[50], day[50], grib_file[256];
        sscanf(query, "latitude=%[^&]&longitude=%[^&]&year=%[^&]&month=%[^&]&day=%[^&]&grib_file=%s",
               latitude, longitude, year, month, day, grib_file);

        MYSQL *conn;
        MYSQL_RES *res;
        MYSQL_ROW row;

        conn = mysql_init(NULL);
        if (mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0) == NULL) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            return MHD_NO;
        }

        char query_buffer[1024];
        snprintf(query_buffer, sizeof(query_buffer),
                 "SELECT MAX(temperature) FROM weather_data WHERE latitude = %s AND longitude = %s "
                 "AND year = %s AND month = %s AND day = %s AND grib_file = '%s'",
                 latitude, longitude, year, month, day, grib_file);

        if (mysql_query(conn, query_buffer)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            mysql_close(conn);
            return MHD_NO;
        }

        res = mysql_use_result(conn);

        char *result = "No data found";
        row = mysql_fetch_row(res);
        if (row != NULL) {
            result = row[0];
        }

        mysql_free_result(res);
        mysql_close(conn);

        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(result), (void *)result, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }

    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}