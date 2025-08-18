#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

// Function prototype
float temperature_for_location(float latitude, float longitude, const char* date);

int main() {
    // Example usage of the function
    float latitude = 40.7128;
    float longitude = -74.0060;
    const char* date = "2023-10-05";

    float temperature = temperature_for_location(latitude, longitude, date);
    
    if (temperature != -1) {
        printf("Temperature: %.2f\n", temperature);
    } else {
        printf("Failed to retrieve temperature.\n");
    }

    return 0;
}

float temperature_for_location(float latitude, float longitude, const char* date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize MySQL connection
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return -1;
    }

    // Connect to the database
    if (mysql_real_connect(conn, "host", "user", "password", "database", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    // Prepare the query
    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM weather_data WHERE latitude = %.6f AND longitude = %.6f AND date = '%s'", 
             latitude, longitude, date);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query execution failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    res = mysql_use_result(conn);

    float temperature = -1.0;

    // Fetch the result
    while ((row = mysql_fetch_row(res))) {
        if (row[0]) {
            temperature = atof(row[0]);
        }
    }

    // Clean up
    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}