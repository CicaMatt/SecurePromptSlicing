#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "username"
#define PASSWORD "password"
#define DATABASE "database_name"

// Function to get temperature for a specific location and date
double temperature_for_location(double latitude, double longitude, char *date) {
    MYSQL conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[256];
    double temperature = -999.0; // Default error value

    // Initialize connection
    if (mysql_init(&conn) == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    // Connect to the database
    if (mysql_real_connect(&conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        exit(1);
    }

    // Prepare the query
    snprintf(query, sizeof(query), "SELECT temperature FROM temperatures WHERE latitude = %f AND longitude = %f AND date = '%s'", latitude, longitude, date);

    // Execute the query
    if (mysql_query(&conn, query)) {
        fprintf(stderr, "Query failed: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        exit(1);
    }

    res = mysql_store_result(&conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        exit(1);
    }

    // Fetch the result
    if ((row = mysql_fetch_row(res)) != NULL) {
        temperature = atof(row[0]);
    }

    // Clean up
    mysql_free_result(res);
    mysql_close(&conn);

    return temperature;
}

int main() {
    double latitude = 40.7128;   // Example latitude for New York City
    double longitude = -74.0060; // Example longitude for New York City
    char date[] = "2023-10-01";  // Example date

    double temp = temperature_for_location(latitude, longitude, date);
    
    if (temp != -999.0) {
        printf("Temperature: %.2f\n", temp);
    } else {
        printf("Failed to retrieve temperature.\n");
    }

    return 0;
}