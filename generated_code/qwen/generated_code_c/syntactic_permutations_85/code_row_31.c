#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "weather_data.db"

int get_temperature_from_db(double lat, double lon, const char *date, double *temperature) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *sql = "SELECT temperature FROM weather WHERE latitude = ? AND longitude = ? AND date = ?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_double(stmt, 1, lat);
    sqlite3_bind_double(stmt, 2, lon);
    sqlite3_bind_text(stmt, 3, date, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
    } else {
        fprintf(stderr, "No data found for the given location and date\n");
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

double temperature_for_location(double latitude, double longitude, const char *date) {
    double temperature;
    if (get_temperature_from_db(latitude, longitude, date, &temperature) != 0) {
        fprintf(stderr, "Error retrieving temperature\n");
        return -1.0; // Indicate error
    }
    return temperature;
}

int main() {
    double latitude = 37.7749; // Example latitude for San Francisco
    double longitude = -122.4194; // Example longitude for San Francisco
    const char *date = "2023-10-01"; // Example date

    double temperature = temperature_for_location(latitude, longitude, date);
    if (temperature != -1.0) {
        printf("Temperature at latitude %.6f, longitude %.6f on %s is %.2f°C\n", latitude, longitude, date, temperature);
    }

    return 0;
}