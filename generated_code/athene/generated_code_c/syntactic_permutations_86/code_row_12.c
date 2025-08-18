#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8080

int handle_request(void *cls, struct MHD_Connection *connection,
                   const char *url, const char *method,
                   const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        return MHD_NO;
    }

    char query[256];
    const char *request_data = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "data");
    if (request_data == NULL) {
        mysql_close(conn);
        return MHD_NO;
    }

    double lat, lon;
    int year, month, day;
    char grib_file[64];

    sscanf(request_data, "%lf,%lf,%d,%d,%d,%63s", &lat, &lon, &year, &month, &day, grib_file);

    snprintf(query, sizeof(query), "SELECT MAX(temp) FROM weather_data WHERE lat=%f AND lon=%f AND year=%d AND month=%d AND day=%d AND grib_file='%s'",
             lat, lon, year, month, day, grib_file);
    
    if (mysql_query(conn, query)) {
        mysql_close(conn);
        return MHD_NO;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        mysql_close(conn);
        return MHD_NO;
    }

    row = mysql_fetch_row(res);
    char response[32];
    if (row != NULL && strcmp(row[0], "") != 0) {
        snprintf(response, sizeof(response), "Max Temp: %s", row[0]);
    } else {
        snprintf(response, sizeof(response), "No data found");
    }

    mysql_free_result(res);
    mysql_close(conn);

    struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response),
                                                                 (void *)response,
                                                                 MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, resp);
    MHD_destroy_response(resp);
    return ret;
}

int main(void) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_IN_THREAD, PORT, NULL, NULL,
                              &handle_request, NULL, MHD_OPTION_END);
    if (daemon == NULL)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}