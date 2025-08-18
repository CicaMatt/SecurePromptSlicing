#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "Sensor.db"

int get_temperature_for_date(sqlite3 *db, double latitude, double longitude, const char *date, double *temperature) {
    sqlite3_stmt *stmt;
    int rc;
    const char *query = "SELECT temperature FROM sensor_data WHERE latitude = ? AND longitude = ? AND date = ?";

    if ((rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0)) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    sqlite3_bind_double(stmt, 1, latitude);
    sqlite3_bind_double(stmt, 2, longitude);
    sqlite3_bind_text(stmt, 3, date, -1, SQLITE_STATIC);

    if ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
    } else if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to step statement: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    return rc;
}

double temperature_for_location(double latitude, double longitude, const char *date) {
    sqlite3 *db;
    int rc;
    double temperature = -999.0; // Default value indicating failure

    if ((rc = sqlite3_open(DATABASE, &db)) != SQLITE_OK) {
        fprintf(stderr, "Failed to open database: %s\n", sqlite3_errmsg(db));
        return temperature;
    }

    rc = get_temperature_for_date(db, latitude, longitude, date, &temperature);
    if (rc != SQLITE_ROW) {
        fprintf(stderr, "No data found for the given location and date.\n");
    }

    sqlite3_close(db);
    return temperature;
}

int main() {
    double latitude = 40.7128; // Example latitude
    double longitude = -74.0060; // Example longitude
    const char *date = "2023-10-01"; // Example date

    double temperature = temperature_for_location(latitude, longitude, date);
    printf("Temperature: %.2f\n", temperature);

    return 0;
}