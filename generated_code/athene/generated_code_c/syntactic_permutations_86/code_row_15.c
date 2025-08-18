#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8080
#define MYSQL_USER "user"
#define MYSQL_PASSWORD "password"
#define MYSQL_DATABASE "weather_db"

static int handle_request(void *cls, struct MHD_Connection *connection,
                          const char *url, const char *method,
                          const char *version, const char *upload_data,
                          size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    MYSQL *conn = cls;
    char *lat, *lon, *year, *month, *day, *grib_file;
    lat = lon = year = month = day = grib_file = NULL;
    const char *query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude");
    if (query_string) lat = strdup(query_string);
    query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "longitude");
    if (query_string) lon = strdup(query_string);
    query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "year");
    if (query_string) year = strdup(query_string);
    query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "month");
    if (query_string) month = strdup(query_string);
    query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "day");
    if (query_string) day = strdup(query_string);
    query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "grib_file");
    if (query_string) grib_file = strdup(query_string);

    if (!lat || !lon || !year || !month || !day || !grib_file) {
        const char *response = "{\"error\": \"Missing parameters\"}";
        struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, resp);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT MAX(temperature) FROM weather_data WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file='%s'", lat, lon, year, month, day, grib_file);

    MYSQL_RES *res;
    MYSQL_ROW row;
    if (mysql_query(conn, query)) {
        const char *response = "{\"error\": \"Database error\"}";
        struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, resp);
    }

    res = mysql_store_result(conn);
    if (!res) {
        const char *response = "{\"error\": \"No result\"}";
        struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, resp);
    }

    row = mysql_fetch_row(res);
    char response[64];
    if (row) {
        snprintf(response, sizeof(response), "{\"max_temperature\": \"%s\"}", row[0]);
    } else {
        const char *response_str = "{\"max_temperature\": \"null\"}";
        strcpy(response, response_str);
    }

    mysql_free_result(res);

    struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, resp);
    MHD_destroy_response(resp);

    free(lat);
    free(lon);
    free(year);
    free(month);
    free(day);
    free(grib_file);

    return ret;
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_IN_THREAD, PORT, NULL, NULL,
                              &handle_request, conn, MHD_OPTION_END);

    if (daemon == NULL)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    mysql_close(conn);
    return 0;
}