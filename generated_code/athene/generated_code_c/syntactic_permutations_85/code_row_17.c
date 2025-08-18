#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11];
} LocationData;

double get_temperature_from_db(sqlite3 *db, const LocationData *location) {
    sqlite3_stmt *stmt;
    double temperature = -999.0;

    const char *sql = "SELECT temperature FROM Sensor WHERE latitude=? AND longitude=? AND date=?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return temperature;
    }

    sqlite3_bind_double(stmt, 1, location->latitude);
    sqlite3_bind_double(stmt, 2, location->longitude);
    sqlite3_bind_text(stmt, 3, location->date, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        temperature = sqlite3_column_double(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return temperature;
}

double temperature_for_location(LocationData *location) {
    sqlite3 *db;
    const char *db_filename = "sensor.db";
    double temperature;

    if (sqlite3_open(db_filename, &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return -999.0;
    }

    temperature = get_temperature_from_db(db, location);

    sqlite3_close(db);
    return temperature;
}

int main() {
    LocationData location = {40.7128, -74.0060, "2023-10-05"};
    double temperature = temperature_for_location(&location);
    printf("Temperature: %.2f\n", temperature);
    return 0;
}