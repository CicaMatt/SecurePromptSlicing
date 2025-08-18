#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "weather_db"

float temperature_for_location(float latitude) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize connection
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    // Connect to the database
    if (mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    // Prepare query
    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM temperatures WHERE latitude = %.6f LIMIT 1;", latitude);

    // Execute query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    // Fetch result
    row = mysql_fetch_row(res);
    float temperature = 0.0;
    if (row != NULL && row[0] != NULL) {
        temperature = atof(row[0]);
    }

    // Cleanup
    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}

int main() {
    float latitude = 37.7749; // Example latitude for San Francisco, CA
    float temp = temperature_for_location(latitude);
    printf("Temperature: %.2f\n", temp);
    return 0;
}