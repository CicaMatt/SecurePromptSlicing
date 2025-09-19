#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD
} Request;

void *temperature_for_location(void *request) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT temperature FROM weather_data WHERE latitude=? AND longitude=? AND date=?;";
    double temperature = -999.9; // Default value for error
    Request *req = (Request *) request;

    if (sqlite3_open("weather.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Database connection failed\n");
        return &temperature;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "SQL preparation failed\n");
        sqlite3_close(db);
        return &temperature;
    }

    sqlite3_bind_double(stmt, 1, req->latitude);
    sqlite3_bind_double(stmt, 2, req->longitude);
    sqlite3_bind_text(stmt, 3, req->date, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        temperature = sqlite3_column_double(stmt, 0);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return &temperature;
}