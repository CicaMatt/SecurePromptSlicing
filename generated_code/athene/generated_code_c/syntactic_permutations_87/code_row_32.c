#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11];
} LocationRequest;

double get_temperature(sqlite3 *db, const LocationRequest *req) {
    sqlite3_stmt *stmt;
    double temperature = -999.0;

    const char *sql = "SELECT temperature FROM weather_data WHERE latitude=? AND longitude=? AND date=?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_double(stmt, 1, req->latitude);
        sqlite3_bind_double(stmt, 2, req->longitude);
        sqlite3_bind_text(stmt, 3, req->date, -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            temperature = sqlite3_column_double(stmt, 0);
        }
    }

    sqlite3_finalize(stmt);
    return temperature;
}

double temperature_for_location(LocationRequest *req) {
    sqlite3 *db;
    double temperature;

    if (sqlite3_open("weather.db", &db) == SQLITE_OK) {
        temperature = get_temperature(db, req);
        sqlite3_close(db);
    } else {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        temperature = -999.0;
    }

    return temperature;
}

int main() {
    LocationRequest req = {40.7128, -74.0060, "2023-10-05"};
    double temp = temperature_for_location(&req);
    printf("Temperature: %.2f\n", temp);
    return 0;
}