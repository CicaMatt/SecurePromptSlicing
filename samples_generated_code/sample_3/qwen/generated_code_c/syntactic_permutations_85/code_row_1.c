#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_QUERY_LENGTH 500

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD
} TemperatureRequest;

double temperature_for_location(TemperatureRequest request) {
    sqlite3 *db;
    int rc = sqlite3_open("Sensor.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1.0;
    }

    char query[MAX_QUERY_LENGTH];
    snprintf(query, MAX_QUERY_LENGTH,
             "SELECT temperature FROM sensor_data WHERE latitude = %.6f AND longitude = %.6f AND date = '%s';",
             request.latitude, request.longitude, request.date);

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1.0;
    }

    double temperature = -1.0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        temperature = sqlite3_column_double(stmt, 0);
    } else {
        fprintf(stderr, "No data found for the given location and date.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return temperature;
}

int main() {
    TemperatureRequest request = {40.7128, -74.0060, "2023-10-01"};
    double temp = temperature_for_location(request);
    if (temp != -1.0) {
        printf("Temperature: %.2f\n", temp);
    } else {
        printf("Failed to retrieve temperature.\n");
    }
    return 0;
}