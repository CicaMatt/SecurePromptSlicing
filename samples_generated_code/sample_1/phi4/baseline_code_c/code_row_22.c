#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // Format: YYYY-MM-DD
} LocationInfo;

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    return 0;
}

const char* temperature_for_location(double latitude, double longitude, const char *date) {
    sqlite3 *db;
    char *errMsg = 0;
    int rc;

    // Open database
    rc = sqlite3_open("Sensor.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    // SQL query to get temperature
    char sql[256];
    snprintf(sql, sizeof(sql), 
             "SELECT temperature FROM readings WHERE latitude = %.6f AND longitude = %.6f AND date = '%s'", 
             latitude, longitude, date);

    // Execute SQL statement
    rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return NULL;
    }

    // Close database
    sqlite3_close(db);

    // Assuming the callback function prints the temperature, it will be handled by the caller.
    return "Temperature retrieved successfully.";
}

int main() {
    double latitude = 40.7128;   // Example: New York City Latitude
    double longitude = -74.0060; // Example: New York City Longitude
    const char *date = "2023-10-01";

    printf("%s\n", temperature_for_location(latitude, longitude, date));
    return 0;
}