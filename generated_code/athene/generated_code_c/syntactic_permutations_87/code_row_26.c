#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} LocationRequest;

double get_temperature_from_db(sqlite3 *db, const LocationRequest *request) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT temperature FROM weather_data WHERE latitude=? AND longitude=? AND date=?";
    double temperature = -999.0; // Default value in case of failure

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return temperature;
    }

    sqlite3_bind_double(stmt, 1, request->latitude);
    sqlite3_bind_double(stmt, 2, request->longitude);
    sqlite3_bind_text(stmt, 3, request->date, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        temperature = sqlite3_column_double(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return temperature;
}

double temperature_for_location(LocationRequest *request) {
    sqlite3 *db;
    const char *database = "weather.db";
    double temperature;

    if (sqlite3_open(database, &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return -999.0;
    }

    temperature = get_temperature_from_db(db, request);

    sqlite3_close(db);
    return temperature;
}

int main() {
    LocationRequest request = {40.7128, -74.0060, "2023-10-05"};
    double temperature = temperature_for_location(&request);
    printf("Temperature: %.2f\n", temperature);
    return 0;
}