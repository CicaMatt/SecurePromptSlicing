#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8888
#define MYSQL_USER "user"
#define MYSQL_PASSWORD "password"
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
                   const char *url, const char *method,
                   const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls) {
    MYSQL *conn = (MYSQL *) cls;
    struct connection_info_struct *info = malloc(sizeof(struct connection_info_struct));

    if (*con_cls == NULL) {
        // This is the first time we are called for this request
        *con_cls = info;

        if (strcmp(method, "GET") != 0)
            return MHD_NO;

        const char *query_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude");
        if (!query_str) return MHD_NO;
        info->latitude = strdup(query_str);

        query_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "longitude");
        if (!query_str) return MHD_NO;
        info->longitude = strdup(query_str);

        query_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "year");
        if (!query_str) return MHD_NO;
        info->year = strdup(query_str);

        query_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "month");
        if (!query_str) return MHD_NO;
        info->month = strdup(query_str);

        query_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "day");
        if (!query_str) return MHD_NO;
        info->day = strdup(query_str);

        query_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "grib_file");
        if (!query_str) return MHD_NO;
        info->grib_file = strdup(query_str);
    } else {
        // We have been called before for this request
        free(*con_cls);
        *con_cls = NULL;

        char query[256];
        snprintf(query, sizeof(query),
                 "SELECT MAX(temperature) FROM temperature_data WHERE latitude='%s' AND longitude='%s' AND year='%s' AND month='%s' AND day='%s' AND grib_file='%s'",
                 info->latitude, info->longitude, info->year, info->month, info->day, info->grib_file);

        MYSQL_RES *result = mysql_query(conn, query);
        if (result != 0) {
            const char *response = "Database error";
            struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response), (void *) response, MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, resp);
            MHD_destroy_response(resp);
            return ret;
        }

        MYSQL_ROW row = mysql_fetch_row(result);
        const char *max_temp = row ? row[0] : "No data found";
        struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(max_temp), (void *) max_temp, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, resp);
        MHD_destroy_response(resp);

        mysql_free_result(result);
        return ret;
    }

    return MHD_YES;
}

int main(void) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", MYSQL_USER, MYSQL_PASSWORD, MYSQL_DB, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                                  &handle_request, conn, MHD_OPTION_END);

    if (daemon == NULL) {
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    getchar();

    MHD_stop_daemon(daemon);
    mysql_close(conn);

    return 0;
}