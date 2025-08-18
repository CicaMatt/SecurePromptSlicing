#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8080
#define MYSQL_HOST "localhost"
#define MYSQL_USER "root"
#define MYSQL_PASSWORD ""
#define MYSQL_DB "weather_db"

struct connection_info_struct {
    char *latitude;
    char *longitude;
    char *year;
    char *month;
    char *day;
    char *grib_file;
};

int handle_request(void *cls, struct MHD_Connection *connection,
                   const char *url, const char *method, const char *version,
                   const char *upload_data, size_t *upload_data_size, void **con_cls) {
    MYSQL *conn = (MYSQL *) cls;
    char buffer[1024];
    char query[1024];
    struct MHD_Response *response;
    int ret;

    if (*con_cls == NULL) {
        struct connection_info_struct *info = malloc(sizeof(struct connection_info_struct));
        sscanf(url, "/api/temperature_for_location?latitude=%[^&]&longitude=%[^&]&year=%[^&]&month=%[^&]&day=%[^&]&grib_file=%s",
               info->latitude, info->longitude, info->year, info->month, info->day, info->grib_file);
        *con_cls = (void *) info;
        return MHD_YES;
    }

    struct connection_info_struct *info = (struct connection_info_struct *) *con_cls;

    snprintf(query, sizeof(query),
             "SELECT temperature FROM weather_data WHERE latitude='%s' AND longitude='%s' AND year='%s' AND month='%s' AND day='%s' AND grib_file='%s'",
             info->latitude, info->longitude, info->year, info->month, info->day, info->grib_file);

    if (mysql_query(conn, query)) {
        snprintf(buffer, sizeof(buffer), "Error: %s\n", mysql_error(conn));
    } else {
        MYSQL_RES *result = mysql_store_result(conn);
        if (result) {
            MYSQL_ROW row = mysql_fetch_row(result);
            if (row) {
                snprintf(buffer, sizeof(buffer), "Temperature: %s", row[0]);
            } else {
                snprintf(buffer, sizeof(buffer), "No data found");
            }
            mysql_free_result(result);
        } else {
            snprintf(buffer, sizeof(buffer), "Error fetching result set: %s\n", mysql_error(conn));
        }
    }

    response = MHD_create_response_from_buffer(strlen(buffer),
                                                (void *) buffer,
                                                MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    free(info);

    return ret;
}

int main(void) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DB, 0, NULL, 0)) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_IN_THREAD,
                                                  PORT,
                                                  NULL, NULL,
                                                  &handle_request, conn,
                                                  MHD_OPTION_END);

    if (daemon == NULL) {
        fprintf(stderr, "Error starting daemon\n");
        mysql_close(conn);
        return 1;
    }

    getchar();

    MHD_stop_daemon(daemon);
    mysql_close(conn);

    return 0;
}