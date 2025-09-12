#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assuming a library like sqlite3 for SQLite database interaction
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} LocationData;

int temperature_for_location(sqlite3 *db, const LocationData *location_data) {
    if (db == NULL || location_data == NULL) {
        return -1; // Error code for invalid input
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM Sensor WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             location_data->latitude, location_data->longitude, location_data->date);

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        return -1; // Error code for database error
    }

    double temperature = 0.0;
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        temperature = sqlite3_column_double(stmt, 0);
    } else if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1; // Error code for database error
    }

    sqlite3_finalize(stmt);

    printf("Temperature: %.2f\n", temperature);
    return 0;
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("sensor.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    LocationData location_data = {37.7749, -122.4194, "2023-10-01"}; // Example data
    temperature_for_location(db, &location_data);

    sqlite3_close(db);
    return 0;
}