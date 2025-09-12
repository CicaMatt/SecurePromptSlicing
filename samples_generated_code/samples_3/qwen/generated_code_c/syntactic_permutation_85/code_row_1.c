#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "Sensor.db"

int get_temperature_from_db(double latitude, double longitude, const char* date, double* temperature) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char* query = "SELECT temperature FROM readings WHERE latitude=? AND longitude=? AND date=?";
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
        fprintf(stderr, "No data found\n");
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

int temperature_for_location(double latitude, double longitude, const char* date, double* temperature) {
    return get_temperature_from_db(latitude, longitude, date, temperature);
}

int main() {
    double latitude = 40.7128; // Example latitude
    double longitude = -74.0060; // Example longitude
    const char* date = "2023-10-01"; // Example date
    double temperature;

    if (temperature_for_location(latitude, longitude, date, &temperature) == 0) {
        printf("Temperature at %.4f, %.4f on %s is %.2f\n", latitude, longitude, date, temperature);
    } else {
        printf("Failed to retrieve temperature\n");
    }

    return 0;
}