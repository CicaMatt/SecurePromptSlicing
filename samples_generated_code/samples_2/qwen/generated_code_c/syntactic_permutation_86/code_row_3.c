#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8888

MYSQL *conn;

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strncmp(url, "/api/temperature_for_location?", 28) != 0)
        return MHD_NO;

    const char *latitude = strchr(url + 28, 'l') + 9;
    const char *longitude = strchr(latitude, '&') + 10;
    const char *year = strchr(longitude, '&') + 5;
    const char *month = strchr(year, '&') + 6;
    const char *day = strchr(month, '&') + 4;
    const char *grib_file = strchr(day, '&') + 9;

    char query[256];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM temperature_data WHERE latitude=%.6f AND longitude=%.6f AND year=%d AND month=%d AND day=%d AND grib_file='%s'",
             atof(latitude), atof(longitude), atoi(year), atoi(month), atoi(day), grib_file);

    if (mysql_query(conn, query)) {
        return MHD_NO;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row;

    char response[128] = "Temperature: ";
    if ((row = mysql_fetch_row(result))) {
        strcat(response, row[0]);
    } else {
        strcat(response, "Not found");
    }
    mysql_free_result(result);

    struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(response),
                                                                         (void *) response,
                                                                         MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
    MHD_destroy_response(response_obj);

    return ret;
}

int main() {
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) {
        return 1;
    }

    getchar();

    mysql_close(conn);
    MHD_stop_daemon(daemon);
    return 0;
}