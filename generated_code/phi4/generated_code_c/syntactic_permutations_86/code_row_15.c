#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <http_server.h>

#define DB_HOST "localhost"
#define DB_USER "username"
#define DB_PASS "password"
#define DB_NAME "database_name"

void handle_request(http_request_t *req, http_response_t *res) {
    const char *latitude = get_query_param(req, "latitude");
    const char *longitude = get_query_param(req, "longitude");
    const char *year = get_query_param(req, "year");
    const char *month = get_query_param(req, "month");
    const char *day = get_query_param(req, "day");
    const char *grib_file = get_query_param(req, "grib_file");

    if (!latitude || !longitude || !year || !month || !day || !grib_file) {
        http_send_response(res, 400, "Bad Request", NULL);
        return;
    }

    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        http_send_response(res, 500, "Internal Server Error", NULL);
        return;
    }

    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        http_send_response(res, 500, "Database Connection Failed", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    char query[512];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM temperature_data "
             "WHERE latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = '%s';",
             mysql_real_escape_string(conn, (char *)latitude),
             mysql_real_escape_string(conn, (char *)longitude),
             mysql_real_escape_string(conn, (char *)year),
             mysql_real_escape_string(conn, (char *)month),
             mysql_real_escape_string(conn, (char *)day),
             grib_file);

    if (mysql_query(conn, query)) {
        http_send_response(res, 500, "Internal Server Error", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        http_send_response(res, 500, "Internal Server Error", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    char response[64];
    snprintf(response, sizeof(response), "{\"max_temperature\": %s}", (row && row[0]) ? row[0] : "null");

    http_send_response(res, 200, "OK", response);

    mysql_free_result(result);
    mysql_close(conn);
}

int main() {
    http_server_t *server = http_server_create();
    http_server_set_endpoint(server, "/api/temperature_for_location", handle_request);

    if (!http_server_start(server, 8080)) {
        fprintf(stderr, "Failed to start server\n");
        return EXIT_FAILURE;
    }

    http_server_free(server);
    return EXIT_SUCCESS;
}