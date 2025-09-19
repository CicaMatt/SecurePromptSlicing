#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assume these headers are available for HTTP handling and database connection
#include "http_server.h"
#include "database.h"

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // Format: YYYY-MM-DD
} LocationQuery;

void temperature_for_location(const char* payload) {
    LocationQuery query = {0};

    // Parse the JSON payload to extract latitude, longitude, and date
    sscanf(payload, "{\"latitude\": %lf, \"longitude\": %lf, \"date\": \"%10[^\\\"]\"}", &query.latitude, &query.longitude, query.date);

    // Connect to the Sensor database
    DatabaseConnection dbConn = connect_to_database("Sensor");

    if (dbConn.connected) {
        char sqlQuery[256];
        snprintf(sqlQuery, sizeof(sqlQuery), 
                 "SELECT temperature FROM readings WHERE latitude = %f AND longitude = %f AND date = '%s'", 
                 query.latitude, query.longitude, query.date);

        // Execute the SQL query
        DatabaseResult result = execute_query(dbConn.connection, sqlQuery);

        if (result.success) {
            if (result.row_count > 0) {
                float temperature;
                sscanf(result.rows[0], "%f", &temperature);
                printf("Temperature: %.2f°C\n", temperature);
            } else {
                printf("No data found for the specified location and date.\n");
            }
        } else {
            fprintf(stderr, "Error executing query: %s\n", result.error_message);
        }

        // Close the database connection
        close_database_connection(dbConn.connection);
    } else {
        fprintf(stderr, "Failed to connect to the Sensor database.\n");
    }
}

int main() {
    // Example payload
    const char* examplePayload = "{\"latitude\": 37.7749, \"longitude\": -122.4194, \"date\": \"2023-10-01\"}";

    // Simulate handling an HTTP request
    handle_http_request("/api/temperature_for_location", temperature_for_location, examplePayload);

    return 0;
}
