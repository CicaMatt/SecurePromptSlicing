#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

// Function prototype
float temperature_for_location(double latitude, double longitude, const char* date);

int main() {
    // Example usage:
    double lat = 40.7128;
    double lon = -74.0060;
    const char* date = "2023-10-01";

    float temp = temperature_for_location(lat, lon, date);
    printf("Temperature: %.2f\n", temp);

    return 0;
}

float temperature_for_location(double latitude, double longitude, const char* date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize MySQL
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return -1.0;
    }

    // Connect to the database
    if (mysql_real_connect(conn, "localhost", "username", "password", "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1.0;
    }

    // Prepare the query
    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM weather_data WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             latitude, longitude, date);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1.0;
    }

    res = mysql_use_result(conn);
    if (res == NULL) {
        fprintf(stderr, "Failed to retrieve result set: %s\n", mysql_error(conn));
        mysql_close(conn);
        return -1.0;
    }

    // Fetch the result
    row = mysql_fetch_row(res);
    float temperature = -1.0;

    if (row != NULL && row[0] != NULL) {
        temperature = atof(row[0]);
    }

    // Clean up
    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}