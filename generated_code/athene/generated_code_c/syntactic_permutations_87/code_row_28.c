#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11];
} LocationRequest;

double get_temperature(sqlite3 *db, const LocationRequest *req) {
    sqlite3_stmt *stmt;
    double temperature = -999.0; // Default value in case of failure

    const char *sql = "SELECT temperature FROM weather_data WHERE latitude=? AND longitude=? AND date=?;";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return temperature;
    }

    sqlite3_bind_double(stmt, 1, req->latitude);
    sqlite3_bind_double(stmt, 2, req->longitude);
    sqlite3_bind_text(stmt, 3, req->date, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        temperature = sqlite3_column_double(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return temperature;
}

double temperature_for_location(LocationRequest *req) {
    sqlite3 *db;
    const char *db_file = "weather.db";

    if (sqlite3_open(db_file, &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return -999.0; // Error value
    }

    double temperature = get_temperature(db, req);

    sqlite3_close(db);
    return temperature;
}

int main() {
    LocationRequest request = {40.7128, -74.0060, "2023-10-05"};
    double temp = temperature_for_location(&request);
    printf("Temperature: %.2f\n", temp);
    return 0;
}