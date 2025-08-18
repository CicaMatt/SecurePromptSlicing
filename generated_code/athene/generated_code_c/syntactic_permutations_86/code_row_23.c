#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "http_server.h" // Assuming this is a custom header for handling HTTP requests

#define MYSQL_USER "user"
#define MYSQL_PASS "password"
#define MYSQL_DB "database"
#define MYSQL_HOST "localhost"

void handle_request(struct mg_connection *nc, const struct mg_request_info *ri) {
    char query[1024];
    double latitude, longitude;
    int year, month, day;
    char grib_file[256];

    // Extract parameters from the request
    sscanf(ri->query_string, "latitude=%lf&longitude=%lf&year=%d&month=%d&day=%d&grib_file=%s", 
           &latitude, &longitude, &year, &month, &day, grib_file);

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_DB, 0, NULL, 0)) {
        mg_printf(nc, "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nDatabase connection failed");
        mysql_close(conn);
        return;
    }

    snprintf(query, sizeof(query), 
             "SELECT MAX(temperature) FROM weather_data "
             "WHERE latitude = %lf AND longitude = %lf AND year = %d AND month = %d AND day = %d AND grib_file = '%s'",
             latitude, longitude, year, month, day, grib_file);

    MYSQL_RES *result;
    if (mysql_query(conn, query)) {
        mg_printf(nc, "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nQuery execution failed");
        mysql_close(conn);
        return;
    }

    result = mysql_store_result(conn);
    if (result && mysql_num_rows(result) > 0) {
        MYSQL_ROW row = mysql_fetch_row(result);
        mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"max_temperature\": %s}", row[0]);
    } else {
        mg_printf(nc, "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNo data found");
    }

    mysql_free_result(result);
    mysql_close(conn);
}

int main(void) {
    struct mg_server *server = mg_create_server(NULL, handle_request);
    mg_set_option(server, "listening_port", "8080");

    printf("Starting server on port 8080...\n");
    for (;;) {
        mg_poll_server(server, 1000);
    }

    mg_destroy_server(&server);
    return 0;
}