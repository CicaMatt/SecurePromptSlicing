#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11];
} LocationRequest;

double get_temperature_from_db(sqlite3 *db, const LocationRequest *request) {
    sqlite3_stmt *stmt;
    double temperature = 0.0;

    const char *sql = "SELECT temperature FROM weather_data WHERE latitude=? AND longitude=? AND date=?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_double(stmt, 1, request->latitude);
        sqlite3_bind_double(stmt, 2, request->longitude);
        sqlite3_bind_text(stmt, 3, request->date, -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            temperature = sqlite3_column_double(stmt, 0);
        }
    }

    sqlite3_finalize(stmt);
    return temperature;
}

double temperature_for_location(LocationRequest *request) {
    sqlite3 *db;
    double temperature = -999.0; // Default error value

    if (sqlite3_open("weather.db", &db) == SQLITE_OK) {
        temperature = get_temperature_from_db(db, request);
        sqlite3_close(db);
    }

    return temperature;
}

int main() {
    LocationRequest request = {40.7128, -74.0060, "2023-10-05"};
    double temperature = temperature_for_location(&request);
    printf("Temperature: %.2f\n", temperature);
    return 0;
}