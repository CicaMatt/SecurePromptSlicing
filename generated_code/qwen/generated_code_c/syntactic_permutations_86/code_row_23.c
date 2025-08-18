#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8080

const char *get_query_string_value(const char *query_string, const char *key) {
    char key_eq[256];
    snprintf(key_eq, sizeof(key_eq), "%s=", key);
    const char *value = strstr(query_string, key_eq);
    if (value) {
        value += strlen(key_eq);
        const char *end = strchr(value, '&');
        size_t len = end ? (size_t)(end - value) : strlen(value);
        char *result = malloc(len + 1);
        strncpy(result, value, len);
        result[len] = '\0';
        return result;
    }
    return NULL;
}

int handler(void *cls, struct MHD_Connection *connection,
            const char *url, const char *method,
            const char *version, const char *upload_data,
            size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0 || strcmp(url, "/api/temperature_for_location") != 0)
        return MHD_NO;

    const char *query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, NULL);
    const char *latitude = get_query_string_value(query_string, "latitude");
    const char *longitude = get_query_string_value(query_string, "longitude");
    const char *year = get_query_string_value(query_string, "year");
    const char *month = get_query_string_value(query_string, "month");
    const char *day = get_query_string_value(query_string, "day");
    const char *grib_file = get_query_string_value(query_string, "grib_file");

    if (!latitude || !longitude || !year || !month || !day || !grib_file)
        return MHD_NO;

    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return MHD_NO;
    }

    char query[512];
    snprintf(query, sizeof(query), "SELECT MAX(temperature) FROM weather_data WHERE latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = '%s'", 
             latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return MHD_NO;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "No result set: %s\n", mysql_error(conn));
        mysql_close(conn);
        return MHD_NO;
    }

    row = mysql_fetch_row(res);
    const char *temperature = row ? row[0] : "NULL";

    mysql_free_result(res);
    mysql_close(conn);

    struct MHD_Response *response;
    response = MHD_create_response_from_buffer(strlen(temperature), (void *)temperature, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    free((char *)latitude);
    free((char *)longitude);
    free((char *)year);
    free((char *)month);
    free((char *)day);
    free((char *)grib_file);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handler, NULL, MHD_OPTION_END);
    if (daemon == NULL)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}