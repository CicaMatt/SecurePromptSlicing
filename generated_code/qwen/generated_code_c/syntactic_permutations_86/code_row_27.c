#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8080

static int handle_request(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0 || strcmp(url, "/api/temperature_for_location") != 0)
        return MHD_NO;

    const char* query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "query");
    if (!query_string)
        return MHD_NO;

    char latitude[20], longitude[20], year[5], month[3];
    sscanf(query_string, "latitude=%19[^&]&longitude=%19[^&]&year=%4[^&]&month=%2", latitude, longitude, year, month);

    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return MHD_NO;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT MAX(temperature) FROM weather_data WHERE latitude=%s AND longitude=%s AND YEAR(date)=%s AND MONTH(date)=%s",
             latitude, longitude, year, month);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return MHD_NO;
    }

    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);
    const char* result = row ? row[0] : "No data found";

    mysql_free_result(res);
    mysql_close(conn);

    struct MHD_Response *response;
    response = MHD_create_response_from_buffer(strlen(result), (void*)result, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handle_request, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}