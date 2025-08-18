#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "user"
#define DB_PASS "password"
#define DB_NAME "weather_db"

MYSQL *conn;

int connect_to_database() {
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }
    return 0;
}

void close_database_connection() {
    mysql_close(conn);
}

double temperature_for_location(double latitude, double longitude, const char *date) {
    if (connect_to_database()) {
        fprintf(stderr, "Failed to connect to database\n");
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM weather_data WHERE latitude = %.6f AND longitude = %.6f AND date = '%s'", 
             latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        close_database_connection();
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        close_database_connection();
        exit(1);
    }

    double temperature = -999.0; // Default value indicating error
    MYSQL_ROW row;
    if ((row = mysql_fetch_row(result))) {
        temperature = atof(row[0]);
    }

    mysql_free_result(result);
    close_database_connection();

    return temperature;
}

int main() {
    double latitude = 40.7128; // Example latitude for New York City
    double longitude = -74.0060; // Example longitude for New York City
    const char *date = "2023-10-05"; // Example date

    double temperature = temperature_for_location(latitude, longitude, date);
    printf("Temperature: %.2f\n", temperature);

    return 0;
}