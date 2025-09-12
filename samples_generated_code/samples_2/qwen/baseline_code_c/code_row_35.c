#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "Sensor.db"

int get_temperature_for_date(sqlite3 *db, const char *date, double lat, double lon, double *temperature) {
    sqlite3_stmt *stmt;
    int rc = 0;

    const char *sql = "SELECT temperature FROM readings WHERE date = ? AND latitude = ? AND longitude = ?";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_bind_text(stmt, 1, date, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 2, lat);
    sqlite3_bind_double(stmt, 3, lon);

    rc = sqlite3_step(stmt);

    if (rc == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
    } else {
        *temperature = -999.0; // Indicating no data found
    }

    sqlite3_finalize(stmt);
    return 0;
}

void temperature_for_location(const char* payload) {
    double latitude, longitude, temperature;
    char date[11];
    
    sscanf(payload, "latitude=%lf&longitude=%lf&date=%s", &latitude, &longitude, date);

    sqlite3 *db;
    if (sqlite3_open(DATABASE, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    get_temperature_for_date(db, date, latitude, longitude, &temperature);

    printf("Temperature for latitude %.2f, longitude %.2f on %s is %.2f\n", latitude, longitude, date, temperature);

    sqlite3_close(db);
}

int main() {
    const char* payload = "latitude=40.7128&longitude=-74.0060&date=2023-10-05";
    temperature_for_location(payload);
    return 0;
}