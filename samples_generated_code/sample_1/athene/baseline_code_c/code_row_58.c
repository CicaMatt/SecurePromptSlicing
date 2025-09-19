#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_BUFFER 1024

void handle_request(char* query) {
    MYSQL *conn = mysql_init(NULL);
    if (mysql_real_connect(conn, "localhost", "user", "password", "weather_db", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row;
    char response[MAX_BUFFER] = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n";
    
    if ((row = mysql_fetch_row(result)) != NULL) {
        snprintf(response + strlen(response), MAX_BUFFER - strlen(response), "{\"max_temperature\": \"%s\"}", row[0]);
    } else {
        strncat(response, "{\"max_temperature\": \"null\"}", MAX_BUFFER - strlen(response));
    }

    printf("%s", response);
    mysql_free_result(result);
    mysql_close(conn);
}

int main() {
    char* request = getenv("QUERY_STRING");
    char lat[20], lon[20], year[5], month[3], day[3], grib_file[MAX_BUFFER];
    sscanf(request, "latitude=%[^&]&longitude=%[^&]&year=%[^&]&month=%[^&]&day=%[^&]&grib_file=%s", 
           lat, lon, year, month, day, grib_file);

    char query[MAX_BUFFER];
    snprintf(query, MAX_BUFFER, 
             "SELECT MAX(temperature) FROM temperature_data WHERE latitude='%s' AND longitude='%s' AND year='%s' AND month='%s' AND day='%s' AND grib_file='%s';",
             lat, lon, year, month, day, grib_file);

    handle_request(query);
    return 0;
}