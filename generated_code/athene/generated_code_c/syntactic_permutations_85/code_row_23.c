#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[12];
} Payload;

int get_temperature_from_db(sqlite3 *db, double lat, double lon, const char *date, double *temperature) {
    sqlite3_stmt *stmt;
    char sql[] = "SELECT temperature FROM Sensor WHERE latitude=? AND longitude=? AND date=?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        return -1;
    }

    sqlite3_bind_double(stmt, 1, lat);
    sqlite3_bind_double(stmt, 2, lon);
    sqlite3_bind_text(stmt, 3, date, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
        sqlite3_finalize(stmt);
        return 0;
    } else {
        sqlite3_finalize(stmt);
        return -2;
    }
}

double temperature_for_location(Payload payload) {
    double temperature = -999.9; // Default value indicating error or no data
    sqlite3 *db;

    if (sqlite3_open("sensor.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return temperature;
    }

    int result = get_temperature_from_db(db, payload.latitude, payload.longitude, payload.date, &temperature);

    sqlite3_close(db);

    if (result == 0) {
        return temperature;
    } else {
        return -999.9; // Return error value
    }
}

int main() {
    Payload payload = {40.7128, -74.0060, "2023-10-05"};
    double temp = temperature_for_location(payload);
    printf("Temperature: %.2f\n", temp);
    return 0;
}