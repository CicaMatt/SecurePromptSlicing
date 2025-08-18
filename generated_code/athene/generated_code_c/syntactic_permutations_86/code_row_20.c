#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8080
#define MYSQL_USER "user"
#define MYSQL_PASSWORD "password"
#define MYSQL_DB "weather_db"

struct connection_info_struct {
    const char *latitude;
    const char *longitude;
    const char *year;
    const char *month;
    const char *day;
    const char *grib_file;
};

static int handle_request(void *cls, struct MHD_Connection *connection,
                          const char *url, const char *method,
                          const char *version, const char *upload_data,
                          size_t *upload_data_size, void **con_cls) {
    MYSQL *conn = (MYSQL *) cls;
    struct connection_info_struct *info = malloc(sizeof(struct connection_info_struct));
    memset(info, 0, sizeof(struct connection_info_struct));

    if (*con_cls == NULL) {
        char *query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude");
        info->latitude = query_string;
        query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "longitude");
        info->longitude = query_string;
        query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "year");
        info->year = query_string;
        query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "month");
        info->month = query_string;
        query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "day");
        info->day = query_string;
        query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "grib_file");
        info->grib_file = query_string;

        *con_cls = (void *) info;
        return MHD_YES;
    }

    char sql_query[1024];
    snprintf(sql_query, sizeof(sql_query),
             "SELECT MAX(temperature) FROM weather_data WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file='%s'",
             info->latitude, info->longitude, info->year, info->month, info->day, info->grib_file);

    MYSQL_RES *result;
    MYSQL_ROW row;
    if (mysql_query(conn, sql_query) == 0) {
        result = mysql_store_result(conn);
        if ((row = mysql_fetch_row(result)) != NULL) {
            char response[128];
            snprintf(response, sizeof(response), "{\"max_temperature\": \"%s\"}", row[0]);
            struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response),
                                                                         (void *) strdup(response),
                                                                         MHD_RESPMEM_MUST_FREE);
            int ret = MHD_queue_response(connection, MHD_HTTP_OK, resp);
            MHD_destroy_response(resp);
            return ret;
        }
    }

    const char *error_message = "{\"error\": \"No data found\"}";
    struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(error_message),
                                                                 (void *) strdup(error_message),
                                                                 MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, resp);
    MHD_destroy_response(resp);
    return ret;
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
        fprintf(stderr, "MHD_start_daemon failed\n");
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    getchar();
    MHD_stop_daemon(daemon);
    mysql_close(conn);
    return EXIT_SUCCESS;
}