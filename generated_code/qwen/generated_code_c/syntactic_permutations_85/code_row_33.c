#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_QUERY_LENGTH 256

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD
} LocationPayload;

double temperature_for_location(LocationPayload payload) {
    sqlite3 *db;
    char *err_message = 0;
    int rc;
    sqlite3_stmt *stmt;
    double temperature = -999.0; // Default value indicating error

    // Open the database connection
    rc = sqlite3_open("weather_data.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return temperature;
    }

    // Prepare SQL query to get the temperature for the given date
    char query[MAX_QUERY_LENGTH];
    snprintf(query, MAX_QUERY_LENGTH, 
             "SELECT temperature FROM weather_data WHERE latitude = %.6f AND longitude = %.6f AND date = '%s'", 
             payload.latitude, payload.longitude, payload.date);

    // Execute SQL query
    rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    if (rc == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            temperature = sqlite3_column_double(stmt, 0);
        }
    } else {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    }

    // Finalize the statement and close the database connection
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return temperature;
}

int main() {
    LocationPayload payload = {37.7749, -122.4194, "2023-10-01"};
    double temp = temperature_for_location(payload);
    if (temp != -999.0) {
        printf("Temperature: %.2f\n", temp);
    } else {
        printf("Failed to retrieve temperature.\n");
    }
    return 0;
}