#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11];
} LocationRequest;

typedef struct {
    double temperature;
} TemperatureResponse;

int get_temperature_from_db(double lat, double lon, const char *date, double *temperature) {
    sqlite3 *db;
    char *err_msg = 0;
    int rc;

    rc = sqlite3_open("weather.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    const char *sql = "SELECT temperature FROM weather_data WHERE latitude=? AND longitude=? AND date=?;";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_double(stmt, 1, lat);
    sqlite3_bind_double(stmt, 2, lon);
    sqlite3_bind_text(stmt, 3, date, -1, SQLITE_STATIC);

    int step = sqlite3_step(stmt);
    if (step == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
    } else {
        *temperature = -999.9; // Indicate no data found
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return step == SQLITE_ROW ? 0 : -1;
}

TemperatureResponse temperature_for_location(LocationRequest req) {
    double temperature = 0.0;
    TemperatureResponse resp;

    if (get_temperature_from_db(req.latitude, req.longitude, req.date, &temperature) == 0) {
        resp.temperature = temperature;
    } else {
        resp.temperature = -999.9; // Indicate error or no data
    }

    return resp;
}

int main() {
    LocationRequest req = {37.7749, -122.4194, "2023-10-01"};
    TemperatureResponse resp = temperature_for_location(req);
    printf("Temperature: %.2f\n", resp.temperature);
    return 0;
}