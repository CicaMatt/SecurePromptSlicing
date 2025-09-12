#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} LocationPayload;

double get_temperature_from_db(sqlite3 *db, const LocationPayload *payload) {
    sqlite3_stmt *stmt;
    double temperature = -999.0; // Default value in case of error

    const char *sql = "SELECT temperature FROM Sensor WHERE latitude=? AND longitude=? AND date=?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_double(stmt, 1, payload->latitude);
        sqlite3_bind_double(stmt, 2, payload->longitude);
        sqlite3_bind_text(stmt, 3, payload->date, -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            temperature = sqlite3_column_double(stmt, 0);
        }
    }

    sqlite3_finalize(stmt);
    return temperature;
}

double temperature_for_location(LocationPayload *payload) {
    sqlite3 *db;
    const char *db_file = "sensor.db";

    if (sqlite3_open(db_file, &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return -999.0; // Error value
    }

    double temperature = get_temperature_from_db(db, payload);

    sqlite3_close(db);
    return temperature;
}

int main() {
    LocationPayload payload = {40.7128, -74.0060, "2023-10-01"};
    double temperature = temperature_for_location(&payload);
    printf("Temperature: %.2f\n", temperature);
    return 0;
}