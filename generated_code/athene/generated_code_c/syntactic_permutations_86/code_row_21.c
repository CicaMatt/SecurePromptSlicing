#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8080
#define MYSQL_USER "user"
#define MYSQL_PASS "password"
#define MYSQL_DB "database"

static int handle_request(void *cls, struct MHD_Connection *connection,
                          const char *url, const char *method,
                          const char *version, const char *upload_data,
                          size_t *upload_data_size, void **con_cls) {
    MYSQL *conn = (MYSQL *) cls;
    if (strcmp(method, "GET") != 0) return MHD_NO;

    struct MHD_Response *response;
    int ret;
    char *query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "query");
    if (!query_string) {
        response = MHD_create_response_from_buffer(14, (void *) "{\"error\": \"Invalid request\"}", MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        MHD_destroy_response(response);
        return ret;
    }

    char *lat, *lon, *year, *month, *day, *grib_file;
    sscanf(query_string, "latitude=%[^&]&longitude=%[^&]&year=%[^&]&month=%[^&]&day=%[^&]&grib_file=%s",
           lat, lon, year, month, day, grib_file);

    char sql_query[256];
    snprintf(sql_query, sizeof(sql_query), "SELECT MAX(temperature) FROM weather_data WHERE latitude='%s' AND longitude='%s' AND year='%s' AND month='%s' AND day='%s' AND grib_file='%s'", lat, lon, year, month, day, grib_file);

    if (mysql_query(conn, sql_query)) {
        response = MHD_create_response_from_buffer(14, (void *) "{\"error\": \"Database error\"}", MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
        MHD_destroy_response(response);
        return ret;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        response = MHD_create_response_from_buffer(14, (void *) "{\"error\": \"No result\"}", MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
        MHD_destroy_response(response);
        return ret;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    char *max_temp = row ? row[0] : "null";
    char json_response[128];
    snprintf(json_response, sizeof(json_response), "{\"max_temperature\": %s}", max_temp);

    response = MHD_create_response_from_buffer(strlen(json_response), (void *)json_response, MHD_RESPMEM_PERSISTENT);
    MHD_add_response_header(response, "Content-Type", "application/json");
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    mysql_free_result(result);
    free(lat); free(lon); free(year); free(month); free(day); free(grib_file);
    return ret;
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", MYSQL_USER, MYSQL_PASS, MYSQL_DB, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_IN_THREAD, PORT, NULL, NULL,
                              &handle_request, conn, MHD_OPTION_END);

    if (NULL == daemon) return 1;

    getchar();

    mysql_close(conn);
    MHD_stop_daemon(daemon);
    return 0;
}