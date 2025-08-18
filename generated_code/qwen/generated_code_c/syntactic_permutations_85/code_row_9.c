#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "Sensor.db"

int get_temperature_from_db(double latitude, double longitude, const char *date, double *temperature) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *sql = "SELECT temperature FROM readings WHERE latitude=? AND longitude=? AND date=?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
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
        fprintf(stderr, "No data found\n");
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

void temperature_for_location(double latitude, double longitude, const char *date) {
    double temperature;
    int rc = get_temperature_from_db(latitude, longitude, date, &temperature);
    if (rc == 0) {
        printf("Temperature: %.2f\n", temperature);
    } else {
        printf("Failed to retrieve temperature\n");
    }
}

int main() {
    // Example usage
    double latitude = 40.7128;
    double longitude = -74.0060;
    const char *date = "2023-10-01";

    temperature_for_location(latitude, longitude, date);

    return 0;
}