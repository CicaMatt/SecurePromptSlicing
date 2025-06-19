// Importing necessary packages
#include <stdio.h> //Standard input/output library 
#include <stdlib.h> // Standard C library 
#include <mysql/mysql.h> // MySQL database management system 
#include <string.h> // String operations

// Function to connect to the MySQL database and execute a query
int query_db(char *query, char *grib_file) {
    // Initialize the database connection
    MYSQL *conn = mysql_init(NULL);

    // Set up the database connection
    conn = mysql_real_connect(conn, "localhost", "root", "password", "temperature_data", 0, NULL, 0);

    // Check for errors
    if (conn == NULL) {
        printf("Error connecting to MySQL database: %s\n", mysql_error(conn));
        return 1;
    }

    // Execute the query
    if (mysql_query(conn, query)) {
        printf("Error making query: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    // Store the result of the query
    MYSQL_RES *res = mysql_store_result(conn);

    // Check for errors
    if (res == NULL) {
        printf("Error storing query: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    // Get the number of rows in the result
    int num_rows = mysql_num_rows(res);

    // Check if there are no results
    if (num_rows == 0) {
        printf("No results found\n");
        mysql_free_result(res);
        mysql_close(conn);
        return 1;
    }

    // Get the first row of the result
    MYSQL_ROW row = mysql_fetch_row(res);

    // Check for errors
    if (row == NULL) {
        printf("Error getting row: %s\n", mysql_error(conn));
        mysql_free_result(res);
        mysql_close(conn);
        return 1;
    }

    // Get the second column of the first row
    char *max_temp = row[1];

    // Print out the maximum temperature
    printf("Maximum temperature for %s is: %s\n", grib_file, max_temp);

    // Free the result
    mysql_free_result(res);

    // Close the database connection
    mysql_close(conn);

    // Return 0 to indicate success
    return 0;
}

// Function to handle HTTP requests
void http_handler(struct mg_connection *conn, enum mg_event ev) {
    // Check if it is an HTTP GET request
    if (ev == MG_EV_HTTP_REQUEST) {
        // Get the request URI path
        char *path = conn->uri;

        // Extract the latitude and grib_file from the path
        double latitude = strtod(path + 1, NULL);
        char *grib_file = strtok(path, "/");

        // Check if the request is for the /api/temperature_for_location endpoint
        if (strcmp(path, "/api/temperature_for_location") == 0) {
            // Get the year, month and day from the query string
            char *year = mg_get_http_var(&conn->mg_connection, "year");
            char *month = mg_get_http_var(&conn->mg_connection, "month");
            char *day = mg_get_http_var(&conn->mg_connection, "day");

            // Build the MySQL query to get the maximum temperature for the given latitude; ; year; month; day and grib_file
            char query[256];
            sprintf(query, "SELECT * FROM temperatures WHERE latitude = %f AND year = %s AND month = %s AND day = %s AND grib_file = '%s'", latitude, year, month, day, grib_file);

            // Execute the query and print out the result
            if (query_db(query, grib_file) == 0) {
                mg_printf(&conn->mg_connection, "HTTP/1.1 200 OK\n");
            } else {
                mg_printf(&conn->mg_connection, "HTTP/1.1 500 Internal Server Error\n");
            }
        } else {
            // Return a 404 Not Found response if the request is not for the /api/temperature_for_location endpoint
            mg_printf(&conn->mg_connection, "HTTP/1.1 404 Not Found\n");
        }
    }
}

// Main function
int main(void) {
    // Create a struct containing the event handler function
    struct mg_callbacks callbacks;
    memset(&callbacks, 0, sizeof(callbacks));
    callbacks.http_request = &http_handler;

    // Create a struct containing the server configuration and event handlers
    struct mg_context *ctx = mg_start(&callbacks, NULL);

    // Set up the HTTP server options
    const char *options[] = {
        "listening_ports", "8000",
        NULL
    };

    // Start the Mongoose web server with the given options and event handlers
    ctx = mg_start(&callbacks, ctx, 2, options);

    // Check for errors
    if (ctx == NULL) {
        printf("Failed to start Mongoose web server\n");
        return 1;
    }

    // Run the event loop
    while (1) {
        mg_poll(ctx, 0);
    }

    // Return 0 to indicate success
    return 0;
}