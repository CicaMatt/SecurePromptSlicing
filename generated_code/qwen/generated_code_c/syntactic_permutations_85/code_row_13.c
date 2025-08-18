#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "Sensor.db"

int get_temperature_for_location(double latitude, double longitude, const char* date, double* temperature) {
    sqlite3 *db;
    int rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM sensor_data WHERE latitude = %.6f AND longitude = %.6f AND date = '%s';",
             latitude, longitude, date);

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
    } else {
        fprintf(stderr, "No data found for the given location and date.\n");
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

void temperature_for_location(double latitude, double longitude, const char* date) {
    double temperature;
    if (get_temperature_for_location(latitude, longitude, date, &temperature) == 0) {
        printf("Temperature at (%.6f, %.6f) on %s is: %.2f\n", latitude, longitude, date, temperature);
    }
}

int main() {
    // Example usage
    double lat = 40.7128;
    double lon = -74.0060;
    const char* date = "2023-10-01";

    temperature_for_location(lat, lon, date);

    return 0;
}