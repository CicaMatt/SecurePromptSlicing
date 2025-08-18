#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void temperature_for_location(double latitude, double longitude, const char* date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    // Connect to the database (replace with your actual connection details)
    if (!mysql_real_connect(conn, "host", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM weather_data WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    // Fetch and print the result
    while ((row = mysql_fetch_row(res))) {
        printf("Temperature: %s\n", row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    // Example usage
    temperature_for_location(37.7749, -122.4194, "2023-10-01");
    return 0;
}