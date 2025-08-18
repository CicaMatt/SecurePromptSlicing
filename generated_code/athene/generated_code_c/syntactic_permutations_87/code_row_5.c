#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_QUERY_LENGTH 256

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} LocationRequest;

double get_temperature_from_db(double lat, double lon, const char *date) {
    sqlite3 *db;
    char query[MAX_QUERY_LENGTH];
    double temperature = -999.0; // Default value for error or no data

    if (sqlite3_open("weather.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return temperature;
    }

    snprintf(query, MAX_QUERY_LENGTH, 
             "SELECT temperature FROM weather_data WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             lat, lon, date);

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            temperature = sqlite3_column_double(stmt, 0);
        }
        sqlite3_finalize(stmt);
    } else {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_close(db);
    return temperature;
}

double temperature_for_location(LocationRequest *request) {
    double latitude = request->latitude;
    double longitude = request->longitude;
    char date[11];
    strncpy(date, request->date, 11); // Ensure null-termination

    return get_temperature_from_db(latitude, longitude, date);
}