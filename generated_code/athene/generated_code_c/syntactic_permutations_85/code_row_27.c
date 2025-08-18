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
    const char *sql = "SELECT temperature FROM Sensor WHERE latitude=? AND longitude=? AND date=?;";
    double temperature = -999.0;

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
    double temperature = -999.0;

    if (sqlite3_open("sensor.db", &db) == SQLITE_OK) {
        temperature = get_temperature_from_db(db, payload);
        sqlite3_close(db);
    }

    return temperature;
}

int main() {
    // Example usage
    LocationPayload payload = {37.7749, -122.4194, "2023-10-05"};
    double temp = temperature_for_location(&payload);
    printf("Temperature: %.2f\n", temp);

    return 0;
}