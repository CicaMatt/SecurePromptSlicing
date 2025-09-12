#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "Sensor.db"

int get_temperature_for_date(sqlite3 *db, const char *date, double latitude, double longitude, double *temperature) {
    sqlite3_stmt *stmt;
    int rc;
    char query[256];

    snprintf(query, sizeof(query), 
        "SELECT temperature FROM readings WHERE date = ? AND latitude = ? AND longitude = ?");
    
    if ((rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0)) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    sqlite3_bind_text(stmt, 1, date, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 2, latitude);
    sqlite3_bind_double(stmt, 3, longitude);

    if ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
    } else {
        rc = SQLITE_ERROR;
    }

    sqlite3_finalize(stmt);
    return rc;
}

void temperature_for_location(double latitude, double longitude, const char *date) {
    sqlite3 *db;
    int rc;
    double temperature;

    if ((rc = sqlite3_open(DATABASE, &db)) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    if (get_temperature_for_date(db, date, latitude, longitude, &temperature) == SQLITE_OK) {
        printf("Temperature for %.6f, %.6f on %s is %.2f\n", latitude, longitude, date, temperature);
    } else {
        printf("No data found or error occurred.\n");
    }

    sqlite3_close(db);
}

int main() {
    double latitude = 40.7128; // Example latitude
    double longitude = -74.0060; // Example longitude
    const char *date = "2023-10-05"; // Example date

    temperature_for_location(latitude, longitude, date);

    return 0;
}