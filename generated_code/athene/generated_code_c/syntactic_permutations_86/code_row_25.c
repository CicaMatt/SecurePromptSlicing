#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define PORT 8080
#define MYSQL_USER "user"
#define MYSQL_PASSWORD "password"
#define MYSQL_DATABASE "weather_db"

void handle_request(char *latitude, char *longitude, char *month, char *day, char *grib_file) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT MAX(temperature) FROM weather_data WHERE "
             "latitude = '%s' AND longitude = '%s' AND month = '%s' AND day = '%s' AND grib_file = '%s';",
             latitude, longitude, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    MYSQL_ROW row;
    if ((row = mysql_fetch_row(result)) != NULL) {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Maximum Temperature: %s\n", row[0]);
    } else {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("No data found.\n");
    }

    mysql_free_result(result);
    mysql_close(conn);
}

int main() {
    char *latitude = getenv("QUERY_LATITUDE");
    char *longitude = getenv("QUERY_LONGITUDE");
    char *month = getenv("QUERY_MONTH");
    char *day = getenv("QUERY_DAY");
    char *grib_file = getenv("QUERY_GRIB_FILE");

    if (latitude && longitude && month && day && grib_file) {
        handle_request(latitude, longitude, month, day, grib_file);
    } else {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Missing parameters.\n");
    }

    return 0;
}