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
    double temperature = -999.0;
    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT temperature FROM weather_data WHERE latitude = %f AND longitude = %f AND date = '%s';", request->latitude, request->longitude, request->date);
    
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            temperature = sqlite3_column_double(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }
    return temperature;
}

double temperature_for_location(LocationRequest *request) {
    sqlite3 *db;
    if (sqlite3_open("weather.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    double temperature = get_temperature_from_db(db, request);

    sqlite3_close(db);
    return temperature;
}

int main() {
    LocationRequest request = {40.7128, -74.0060, "2023-10-01"};
    double temperature = temperature_for_location(&request);
    printf("Temperature: %.2f\n", temperature);
    return 0;
}