#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "http_server.h" // Assuming this is your HTTP server library

#define MYSQL_HOST "localhost"
#define MYSQL_USER "user"
#define MYSQL_PASSWORD "password"
#define MYSQL_DATABASE "weather"

void handle_request(struct mg_connection *nc, const struct mg_request_info *ri) {
    if (strcmp(ri->uri, "/api/temperature_for_location") == 0 && ri->method != NULL) {
        char *latitude = mg_get_var(ri, "latitude");
        char *longitude = mg_get_var(ri, "longitude");
        char *year = mg_get_var(ri, "year");
        char *month = mg_get_var(ri, "month");
        char *day = mg_get_var(ri, "day");
        char *grib_file = mg_get_var(ri, "grib_file");

        MYSQL *conn = mysql_init(NULL);
        if (mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0) == NULL) {
            mg_printf(nc, "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nDatabase connection failed");
            mysql_close(conn);
            return;
        }

        char query[256];
        snprintf(query, sizeof(query), 
                 "SELECT MAX(temperature) FROM weather_data WHERE latitude='%s' AND longitude='%s' AND year='%s' AND month='%s' AND day='%s' AND grib_file='%s'", 
                 latitude, longitude, year, month, day, grib_file);

        MYSQL_RES *result;
        if (mysql_query(conn, query) != 0) {
            mg_printf(nc, "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nQuery execution failed");
            mysql_close(conn);
            return;
        }

        result = mysql_store_result(conn);
        if (result == NULL) {
            mg_printf(nc, "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nFailed to store result");
            mysql_close(conn);
            return;
        }

        MYSQL_ROW row = mysql_fetch_row(result);
        double max_temp = (row != NULL && row[0] != NULL) ? atof(row[0]) : -999.0;

        mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"max_temperature\": %.2f}", max_temp);

        mysql_free_result(result);
        mysql_close(conn);
    } else {
        mg_printf(nc, "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNot Found");
    }
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