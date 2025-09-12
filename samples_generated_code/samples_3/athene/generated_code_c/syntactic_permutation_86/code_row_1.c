#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "http_parser.h" // Assuming this is a custom header for HTTP parsing

#define MYSQL_USER "user"
#define MYSQL_PASSWORD "password"
#define MYSQL_DATABASE "weather_db"
#define MYSQL_HOST "localhost"

void handle_request(http_parser *parser) {
    double latitude, longitude;
    int year, month, day;
    char grib_file[256];

    // Extract parameters from request
    sscanf(parser->query_string, "?latitude=%lf&longitude=%lf&year=%d&month=%d&day=%d&grib_file=%s",
           &latitude, &longitude, &year, &month, &day, grib_file);

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "MySQL connection error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    char query[1024];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM temperature_data WHERE latitude = %.6f AND longitude = %.6f "
             "AND year = %d AND month = %d AND day = %d AND grib_file = '%s'",
             latitude, longitude, year, month, day, grib_file);

    MYSQL_RES *result;
    if (mysql_query(conn, query)) {
        fprintf(stderr, "MySQL query error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    result = mysql_store_result(conn);
    if (result && mysql_num_rows(result) > 0) {
        MYSQL_ROW row = mysql_fetch_row(result);
        double max_temp = atof(row[0]);
        char response[128];
        snprintf(response, sizeof(response), "{\"max_temperature\": %.2f}", max_temp);
        http_parser_send_response(parser, response, strlen(response));
    } else {
        http_parser_send_response(parser, "{\"error\": \"No data found\"}", 24);
    }

    mysql_free_result(result);
    mysql_close(conn);
}

int main() {
    http_parser_init("/api/temperature_for_location", handle_request);
    return 0;
}