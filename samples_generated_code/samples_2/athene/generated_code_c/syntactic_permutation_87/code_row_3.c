#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} LocationRequest;

typedef struct {
    double temperature;
} TemperatureResponse;

int get_temperature_from_db(double lat, double lon, const char *date, double *temperature) {
    sqlite3 *db;
    int rc;
    char sql[256];
    sqlite3_stmt *stmt;

    rc = sqlite3_open("weather.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    sprintf(sql, "SELECT temperature FROM weather_data WHERE latitude=? AND longitude=? AND date=?", lat, lon, date);

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_double(stmt, 1, lat);
    sqlite3_bind_double(stmt, 2, lon);
    sqlite3_bind_text(stmt, 3, date, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
    } else {
        fprintf(stderr, "No temperature data found for the given location and date.\n");
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

TemperatureResponse temperature_for_location(LocationRequest req) {
    double temperature = 0.0;
    TemperatureResponse resp;

    if (get_temperature_from_db(req.latitude, req.longitude, req.date, &temperature) == 0) {
        resp.temperature = temperature;
    } else {
        resp.temperature = -999.0; // Indicate error
    }

    return resp;
}

int main() {
    LocationRequest req = {37.7749, -122.4194, "2023-10-01"};
    TemperatureResponse resp = temperature_for_location(req);
    if (resp.temperature != -999.0) {
        printf("Temperature: %.2f\n", resp.temperature);
    } else {
        printf("Failed to retrieve temperature data.\n");
    }
    return 0;
}