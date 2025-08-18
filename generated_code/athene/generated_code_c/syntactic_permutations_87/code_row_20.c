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
    double temperature = -999.0; // Default value for error or no data

    const char *sql = "SELECT temperature FROM weather_data WHERE latitude=? AND longitude=? AND date=?;";
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc == SQLITE_OK) {
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
    int rc = sqlite3_open("weather.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    double temperature = get_temperature_from_db(db, request);
    sqlite3_close(db);
    return temperature;
}

int main() {
    // Example usage
    LocationRequest request = {40.7128, -74.0060, "2023-10-05"};
    double temperature = temperature_for_location(&request);
    printf("Temperature: %.2f\n", temperature);

    return 0;
}