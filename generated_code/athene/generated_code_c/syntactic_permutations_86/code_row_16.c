#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8080
#define MYSQL_USER "user"
#define MYSQL_PASSWORD "password"
#define MYSQL_DATABASE "weather_db"

struct connection_info {
    double latitude;
    double longitude;
    int year;
    int month;
    int day;
    char grib_file[256];
};

int handle_request(void *cls, struct MHD_Connection *connection,
                   const char *url, const char *method,
                   const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls) {
    MYSQL *conn = (MYSQL *)cls;
    struct connection_info *info = malloc(sizeof(struct connection_info));
    if (*con_cls == NULL) {
        if (strcmp(method, "GET") != 0)
            return MHD_NO;

        const char *query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude");
        info->latitude = atof(query_string);

        query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "longitude");
        info->longitude = atof(query_string);

        query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "year");
        info->year = atoi(query_string);

        query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "month");
        info->month = atoi(query_string);

        query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "day");
        info->day = atoi(query_string);

        query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "grib_file");
        strncpy(info->grib_file, query_string, sizeof(info->grib_file) - 1);

        *con_cls = info;
        return MHD_YES;
    }

    char query[512];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM weather_data WHERE "
             "latitude=%f AND longitude=%f AND year=%d AND month=%d AND day=%d AND grib_file='%s'",
             info->latitude, info->longitude, info->year, info->month, info->day, info->grib_file);

    MYSQL_RES *result;
    MYSQL_ROW row;

    if (mysql_query(conn, query) == 0) {
        result = mysql_store_result(conn);
        if ((row = mysql_fetch_row(result)) != NULL) {
            char response[64];
            snprintf(response, sizeof(response), "{\"max_temperature\": %s}", row[0]);
            struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response),
                                                                         (void *)response,
                                                                         MHD_RESPMEM_MUST_COPY);
            int ret = MHD_queue_response(connection, MHD_HTTP_OK, resp);
            MHD_destroy_response(resp);
            mysql_free_result(result);
            free(info);
            return ret;
        }
    }

    const char *error_msg = "{\"max_temperature\": null}";
    struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(error_msg),
                                                                 (void *)error_msg,
                                                                 MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, resp);
    MHD_destroy_response(resp);
    free(info);
    return ret;
}

int main(void) {
    MYSQL *conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_IN_THREAD, PORT, NULL, NULL,
                                                  &handle_request, conn, MHD_OPTION_END);

    if (NULL == daemon) {
        fprintf(stderr, "MHD_start_daemon failed\n");
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    getchar();

    MHD_stop_daemon(daemon);
    mysql_close(conn);
    return 0;
}