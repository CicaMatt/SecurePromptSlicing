#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <httpserver/httpserver.h>

#define DATABASE_HOST "localhost"
#define DATABASE_USER "your_username"
#define DATABASE_PASSWORD "your_password"
#define DATABASE_NAME "your_database"

void handle_request(http_request_t *request, void *user_data) {
    char latitude[20];
    char longitude[20];
    int year;
    int month;
    int day;
    char grib_file[256];

    // Extract parameters from the request
    sscanf(request->data, "latitude=%[^&]&longitude=%[^&]&year=%d&month=%d&day=%d&grib_file=%s",
           latitude, longitude, &year, &month, &day, grib_file);

    char query[512];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM temperature_data "
             "WHERE latitude = '%s' AND longitude = '%s' AND year = %d AND month = %d AND day = %d AND grib_file = '%s'",
             latitude, longitude, year, month, day, grib_file);

    MYSQL *conn;
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return;
    }

    if (mysql_real_connect(conn, DATABASE_HOST, DATABASE_USER, DATABASE_PASSWORD,
                           DATABASE_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        return;
    }

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        MYSQL_RES *result = mysql_store_result(conn);
        if (result) {
            MYSQL_ROW row = mysql_fetch_row(result);
            if (row && row[0]) {
                http_response_t response;
                snprintf(response.data, sizeof(response.data), "Max Temperature: %s", row[0]);
                httpserver_send_response(request->client, 200, "application/json", response.data, strlen(response.data));
            } else {
                snprintf(response.data, sizeof(response.data), "{\"error\":\"No data found\"}");
                httpserver_send_response(request->client, 404, "application/json", response.data, strlen(response.data));
            }
            mysql_free_result(result);
        } else {
            fprintf(stderr, "%s\n", mysql_error(conn));
            snprintf(response.data, sizeof(response.data), "{\"error\":\"Query failed\"}");
            httpserver_send_response(request->client, 500, "application/json", response.data, strlen(response.data));
        }
    }

    mysql_close(conn);
}

int main() {
    httpserver_t *server = httpserver_create("0.0.0.0", 8080);

    if (httpserver_add_endpoint(server, "/api/temperature_for_location", handle_request) != 0) {
        fprintf(stderr, "Failed to add endpoint\n");
        return EXIT_FAILURE;
    }

    httpserver_start(server);
    httpserver_destroy(server);

    return EXIT_SUCCESS;
}