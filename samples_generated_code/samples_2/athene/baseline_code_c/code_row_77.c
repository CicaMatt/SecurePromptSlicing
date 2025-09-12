#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11];
} LocationRequest;

double temperature_for_location(LocationRequest *request) {
    sqlite3 *db;
    const char *sql;
    sqlite3_stmt *res;
    double temperature = -999.0; // Default value in case of failure

    if (sqlite3_open("weather.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return temperature;
    }

    sql = "SELECT temperature FROM weather_data WHERE latitude=? AND longitude=? AND date=?";

    if (sqlite3_prepare_v2(db, sql, -1, &res, 0)) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return temperature;
    }

    sqlite3_bind_double(res, 1, request->latitude);
    sqlite3_bind_double(res, 2, request->longitude);
    sqlite3_bind_text(res, 3, request->date, -1, SQLITE_STATIC);

    if (sqlite3_step(res) == SQLITE_ROW) {
        temperature = sqlite3_column_double(res, 0);
    }

    sqlite3_finalize(res);
    sqlite3_close(db);
    return temperature;
}