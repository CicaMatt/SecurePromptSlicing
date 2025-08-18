#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "Sensor.db"

int get_temperature_for_date(sqlite3 *db, double latitude, double longitude, const char *date, double *temperature) {
    sqlite3_stmt *stmt;
    int rc;
    const char *sql = "SELECT temperature FROM sensor_data WHERE latitude=? AND longitude=? AND date=?";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    sqlite3_bind_double(stmt, 1, latitude);
    sqlite3_bind_double(stmt, 2, longitude);
    sqlite3_bind_text(stmt, 3, date, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
    } else {
        fprintf(stderr, "No temperature found for the given location and date.\n");
        sqlite3_finalize(stmt);
        return SQLITE_ERROR;
    }

    sqlite3_finalize(stmt);
    return SQLITE_OK;
}

void temperature_for_location(double latitude, double longitude, const char *date) {
    sqlite3 *db;
    int rc = sqlite3_open(DATABASE, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    double temperature;
    rc = get_temperature_for_date(db, latitude, longitude, date, &temperature);
    if (rc == SQLITE_OK) {
        printf("Temperature for location (%f, %f) on %s is %.2f°C\n", latitude, longitude, date, temperature);
    }

    sqlite3_close(db);
}

int main() {
    double latitude = 40.7128;
    double longitude = -74.0060;
    const char *date = "2023-10-01";

    temperature_for_location(latitude, longitude, date);

    return 0;
}