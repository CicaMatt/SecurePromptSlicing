#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "weather_db"

void handle_error(MYSQL *conn) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
}

double temperature_for_location(double latitude, double longitude, const char *date) {
    MYSQL conn;
    if (mysql_init(&conn) == NULL) {
        fprintf(stderr, "MySQL initialization failed.\n");
        exit(1);
    }

    if (!mysql_real_connect(&conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        handle_error(&conn);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM temperatures WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             latitude, longitude, date);

    if (mysql_query(&conn, query)) {
        handle_error(&conn);
    }

    MYSQL_RES *result = mysql_store_result(&conn);
    if (!result) {
        handle_error(&conn);
    }

    MYSQL_ROW row;
    double temperature = 0.0;

    if ((row = mysql_fetch_row(result))) {
        temperature = atof(row[0]);
    }

    mysql_free_result(result);
    mysql_close(&conn);

    return temperature;
}

int main() {
    // Example usage
    double latitude = 40.7128;
    double longitude = -74.0060;
    const char *date = "2023-10-01";

    double temp = temperature_for_location(latitude, longitude, date);
    printf("Temperature: %.2f\n", temp);

    return 0;
}