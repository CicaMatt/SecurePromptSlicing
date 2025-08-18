#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_QUERY_SIZE 1024

void handle_request(char *latitude, char *year, char *month, char *day, char *grib_file) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "weather_db", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[MAX_QUERY_SIZE];
    snprintf(query, MAX_QUERY_SIZE, 
             "SELECT MAX(temperature) FROM weather_data WHERE latitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = '%s';",
             latitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row != NULL) {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("%s", row[0] ? row[0] : "No data found");
    } else {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("No data found");
    }

    mysql_free_result(result);
    mysql_close(conn);
}

int main() {
    char *latitude = getenv("QUERY_PARAM_LATITUDE");
    char *year = getenv("QUERY_PARAM_YEAR");
    char *month = getenv("QUERY_PARAM_MONTH");
    char *day = getenv("QUERY_PARAM_DAY");
    char *grib_file = getenv("QUERY_PARAM_GRIB_FILE");

    if (latitude && year && month && day && grib_file) {
        handle_request(latitude, year, month, day, grib_file);
    } else {
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Missing parameters");
    }

    return 0;
}