#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "http_parser.h"

#define MYSQL_USER "user"
#define MYSQL_PASSWORD "password"
#define MYSQL_DATABASE "weatherdb"
#define MYSQL_HOST "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 4096

MYSQL *conn;
char *query = "SELECT MAX(temperature) FROM weather_data WHERE latitude=%f AND longitude=%f AND year=%d AND month=%d AND day=%d AND grib_file='%s'";

void handle_request(char *request, char *response) {
    http_parser_settings settings;
    http_parser parser;

    memset(&settings, 0, sizeof(settings));
    http_parser_init(&parser, HTTP_REQUEST);

    struct {
        float latitude, longitude;
        int year, month, day;
        char grib_file[256];
    } params = {0};

    // Parse the request to extract parameters
    if (http_parser_execute(&parser, &settings, request, strlen(request)) == 0) {
        // Extract query parameters from the URL
        const char *query_start = strstr(request, "?");
        if (query_start) {
            sscanf(query_start + 1, "latitude=%f&longitude=%f&year=%d&month=%d&day=%d&grib_file=%s",
                   &params.latitude, &params.longitude, &params.year, &params.month, &params.day, params.grib_file);
        }

        // Connect to MySQL
        conn = mysql_init(NULL);
        if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
            snprintf(response, BUFFER_SIZE, "Connection to database failed: %s", mysql_error(conn));
            return;
        }

        // Prepare and execute the query
        char sql_query[1024];
        sprintf(sql_query, query, params.latitude, params.longitude, params.year, params.month, params.day, params.grib_file);
        if (mysql_query(conn, sql_query)) {
            snprintf(response, BUFFER_SIZE, "Query execution failed: %s", mysql_error(conn));
        } else {
            MYSQL_RES *result = mysql_store_result(conn);
            MYSQL_ROW row;
            if ((row = mysql_fetch_row(result))) {
                snprintf(response, BUFFER_SIZE, "{\"max_temperature\": \"%s\"}", row[0]);
            } else {
                snprintf(response, BUFFER_SIZE, "{\"message\": \"No data found\"}");
            }
            mysql_free_result(result);
        }

        mysql_close(conn);
    } else {
        snprintf(response, BUFFER_SIZE, "Failed to parse request");
    }
}

int main() {
    char buffer[BUFFER_SIZE];
    char response[BUFFER_SIZE];

    // Simple HTTP server (for demonstration purposes)
    while (1) {
        // Simulate receiving a request
        int n = recvfrom(PORT, buffer, BUFFER_SIZE, 0, NULL, NULL);
        if (n > 0) {
            handle_request(buffer, response);
            sendto(PORT, response, strlen(response), 0, NULL, 0);
        }
    }

    return 0;
}