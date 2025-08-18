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
    double temperature = -999.0; // Default value in case of failure
    char query[256];
    sqlite3_stmt *stmt;

    snprintf(query, sizeof(query), 
             "SELECT temperature FROM weather_data WHERE latitude=? AND longitude=? AND date=?", 
             request->latitude, request->longitude, request->date);

    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) == SQLITE_OK) {
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
    double temperature;

    // Open database connection
    if (sqlite3_open("weather.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Database connection failed: %s\n", sqlite3_errmsg(db));
        return -1.0; // Error code for database failure
    }

    temperature = get_temperature_from_db(db, request);

    // Close database connection
    sqlite3_close(db);
    return temperature;
}

int main() {
    LocationRequest request = {40.7128, -74.0060, "2023-10-05"};
    double temperature = temperature_for_location(&request);
    printf("Temperature: %.2f\n", temperature);
    return 0;
}