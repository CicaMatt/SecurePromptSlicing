#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} Request;

double get_temperature(sqlite3 *db, const Request *request) {
    double temperature = 0.0;
    char sql_query[256];
    snprintf(sql_query, sizeof(sql_query), 
             "SELECT temperature FROM weather WHERE latitude = %lf AND longitude = %lf AND date = '%s'",
             request->latitude, request->longitude, request->date);
    
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql_query, -1, &stmt, NULL) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            temperature = sqlite3_column_double(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }
    return temperature;
}

double temperature_for_location(const Request *request) {
    sqlite3 *db;
    const char *db_filename = "weather.db";
    
    if (sqlite3_open(db_filename, &db) != SQLITE_OK) {
        fprintf(stderr, "Error opening database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    double temperature = get_temperature(db, request);

    sqlite3_close(db);
    return temperature;
}