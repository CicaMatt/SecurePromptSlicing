#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

// Function declarations
int getTemperature(sqlite3 *db, const char *latitude, const char *longitude, const char *date, double *temperature);
void handleRequest(const char *payload);

int main() {
    // Simulating a request payload for demonstration purposes.
    const char *requestPayload = "{\"latitude\": \"34.0522\", \"longitude\": \"-118.2437\", \"date\": \"2023-10-01\"}";
    
    // Handle the incoming request
    handleRequest(requestPayload);
    
    return 0;
}

void handleRequest(const char *payload) {
    sqlite3 *db;
    double temperature = 0.0;
    
    // Open database connection
    if (sqlite3_open("temperature_data.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    char latitude[50], longitude[50], date[50];
    sscanf(payload, "{\"latitude\": \"%[^\\\"]\", \"longitude\": \"%[^\\\"]\", \"date\": \"%[^\"]\"}", latitude, longitude, date);

    // Get temperature for the specified location and date
    if (getTemperature(db, latitude, longitude, date, &temperature) != SQLITE_OK) {
        fprintf(stderr, "Failed to retrieve temperature\n");
    } else {
        printf("Temperature: %.2f°C\n", temperature);
    }

    // Close database connection
    sqlite3_close(db);
}

int getTemperature(sqlite3 *db, const char *latitude, const char *longitude, const char *date, double *temperature) {
    char sql[256];
    sprintf(sql, "SELECT temp FROM temperatures WHERE latitude = '%s' AND longitude = '%s' AND date = '%s'", latitude, longitude, date);

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        return SQLITE_ERROR;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
        sqlite3_finalize(stmt);
        return SQLITE_OK;
    } else {
        fprintf(stderr, "No temperature data found for the specified location and date\n");
        sqlite3_finalize(stmt);
        return SQLITE_ERROR;
    }
}