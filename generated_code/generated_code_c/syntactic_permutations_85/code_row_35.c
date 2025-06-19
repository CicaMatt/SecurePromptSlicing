#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

// Define the database connection details
#define DATABASE "database"
#define HOST "localhost"
#define USERNAME "username"
#define PASSWORD "password"

typedef struct {
    double latitude;
    double longitude;
    char date[30];
} location_data;

// Function to connect to the database and get the temperature for the given location and date
int get_temperature(location_data data) {
    // Initialize the database connection handle
    MYSQL *conn;

    // Allocate memory for the query results
    MYSQL_RES *res;

    // Allocate memory for the row
    MYSQL_ROW row;

    // Connect to the database
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, HOST, USERNAME, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        return -1;
    }

    // Build the query string
    char query[256];
    sprintf(query, "SELECT temperature FROM weather WHERE latitude = %.4f AND longitude = %.4f AND date = '%s'", data.latitude, data.longitude, data.date);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        return -1;
    }

    // Get the results of the query
    res = mysql_store_result(conn);

    // Check if any rows were returned
    if (mysql_num_rows(res) == 0) {
        fprintf(stderr, "Error: No data found\n");
        return -1;
    }

    // Get the first row
    row = mysql_fetch_row(res);

    // Return the temperature
    int temperature = atoi(row[0]);

    // Clean up
    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}