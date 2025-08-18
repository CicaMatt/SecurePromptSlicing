#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD
} LocationRequest;

double get_temperature_from_db(double latitude, double longitude, const char *date) {
    sqlite3 *db;
    int rc;
    double temperature = -999.0;

    rc = sqlite3_open("temperature.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return temperature;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), 
             "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?;");

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return temperature;
    }

    sqlite3_bind_double(stmt, 1, latitude);
    sqlite3_bind_double(stmt, 2, longitude);
    sqlite3_bind_text(stmt, 3, date, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        temperature = sqlite3_column_double(stmt, 0);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return temperature;
}

double temperature_for_location(LocationRequest *request) {
    double latitude = request->latitude;
    double longitude = request->longitude;
    const char *date = request->date;

    return get_temperature_from_db(latitude, longitude, date);
}