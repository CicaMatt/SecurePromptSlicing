#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // Assuming format "YYYY-MM-DD"
} Payload;

double temperature_for_location(Payload payload) {
    sqlite3 *db;
    int rc;
    const char *sql;
    sqlite3_stmt *res;
    double temperature = -999.0; // Default value if not found

    rc = sqlite3_open("Sensor.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return temperature;
    }

    sql = "SELECT temperature FROM SensorData WHERE latitude=? AND longitude=? AND date=?";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return temperature;
    }

    sqlite3_bind_double(res, 1, payload.latitude);
    sqlite3_bind_double(res, 2, payload.longitude);
    sqlite3_bind_text(res, 3, payload.date, -1, SQLITE_STATIC);

    if (sqlite3_step(res) == SQLITE_ROW) {
        temperature = sqlite3_column_double(res, 0);
    }

    sqlite3_finalize(res);
    sqlite3_close(db);

    return temperature;
}