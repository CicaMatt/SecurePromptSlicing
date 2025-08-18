#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "Sensor.db"

int get_temperature(double latitude, double longitude, const char *date, double *temperature) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *query = "SELECT temperature FROM sensor_data WHERE latitude=? AND longitude=? AND date(reading_time)=?";
    rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_double(stmt, 1, latitude);
    sqlite3_bind_double(stmt, 2, longitude);
    sqlite3_bind_text(stmt, 3, date, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
    } else {
        *temperature = -999.0; // Indicate no data found
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

void temperature_for_location(double latitude, double longitude, const char *date) {
    double temperature;
    if (get_temperature(latitude, longitude, date, &temperature) == 0) {
        if (temperature != -999.0) {
            printf("Temperature: %.2f\n", temperature);
        } else {
            printf("No temperature data available for the given location and date.\n");
        }
    } else {
        printf("Failed to retrieve temperature data.\n");
    }
}

int main() {
    // Example usage
    double latitude = 37.7749;
    double longitude = -122.4194;
    const char *date = "2023-10-05";

    temperature_for_location(latitude, longitude, date);

    return 0;
}