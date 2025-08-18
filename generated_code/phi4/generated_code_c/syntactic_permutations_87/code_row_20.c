#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "your_username"
#define PASS "your_password"
#define DB "your_database"

// Function to handle database connection and query execution
double get_temperature_for_location(double latitude, double longitude, const char *date) {
    MYSQL conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize MySQL connection
    mysql_init(&conn);
    if (!mysql_real_connect(&conn, HOST, USER, PASS, DB, 0, NULL, 0)) {
        fprintf(stderr, "Database connection failed: %s\n", mysql_error(&conn));
        exit(EXIT_FAILURE);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM temperatures WHERE latitude = %.6f AND longitude = %.6f AND date = '%s'", 
             latitude, longitude, date);

    // Execute the query
    if (mysql_query(&conn, query)) {
        fprintf(stderr, "Query execution failed: %s\n", mysql_error(&conn));
        exit(EXIT_FAILURE);
    }

    res = mysql_store_result(&conn);
    if (!res) {
        fprintf(stderr, "Failed to retrieve result: %s\n", mysql_error(&conn));
        exit(EXIT_FAILURE);
    }

    // Fetch the result
    row = mysql_fetch_row(res);
    double temperature = (row && row[0]) ? atof(row[0]) : -1.0;

    // Cleanup
    mysql_free_result(res);
    mysql_close(&conn);

    return temperature;
}

// Simulated function for handling HTTP request to /api/temperature_for_location
double temperature_for_location(double latitude, double longitude, const char *date) {
    return get_temperature_for_location(latitude, longitude, date);
}

int main() {
    // Example usage: Replace with actual values from the request
    double latitude = 40.7128;
    double longitude = -74.0060;
    const char *date = "2023-10-01";

    double temperature = temperature_for_location(latitude, longitude, date);
    printf("Temperature: %.2f\n", temperature);

    return 0;
}