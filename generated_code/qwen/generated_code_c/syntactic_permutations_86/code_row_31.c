#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8080

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                  const char *url, const char *method,
                                  const char *version, const char *upload_data,
                                  size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strstr(url, "/api/temperature_for_location?")) {
        double latitude, longitude;
        int year, month, day;
        char grib_file[256];
        sscanf(url, "/api/temperature_for_location?latitude=%lf&longitude=%lf&year=%d&month=%d&day=%d&grib_file=%255s",
               &latitude, &longitude, &year, &month, &day, grib_file);

        MYSQL *conn;
        MYSQL_RES *res;
        MYSQL_ROW row;

        conn = mysql_init(NULL);
        if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            return MHD_NO;
        }

        char query[512];
        snprintf(query, sizeof(query),
                 "SELECT MAX(temperature) FROM weather_data WHERE latitude = %lf AND longitude = %lf AND year = %d AND month = %d AND day = %d AND grib_file = '%s'",
                 latitude, longitude, year, month, day, grib_file);

        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            return MHD_NO;
        }

        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        char *result = row ? row[0] : "No data";

        mysql_free_result(res);
        mysql_close(conn);

        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(result),
                                                                         (void *) result, MHD_RESPMEM_PERSISTENT);
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

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}