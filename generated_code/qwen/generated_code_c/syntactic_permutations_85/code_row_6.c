#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "Sensor.db"

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD
} RequestPayload;

double getTemperature(RequestPayload payload) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    double temperature = -999.0; // Default value if no data is found

    rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return temperature;
    }

    const char *query = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
    rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return temperature;
    }

    sqlite3_bind_double(stmt, 1, payload.latitude);
    sqlite3_bind_double(stmt, 2, payload.longitude);
    sqlite3_bind_text(stmt, 3, payload.date, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        temperature = sqlite3_column_double(stmt, 0);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return temperature;
}

int main() {
    RequestPayload payload = {40.7128, -74.0060, "2023-10-05"};
    double temp = getTemperature(payload);
    printf("Temperature: %.2f\n", temp);
    return 0;
}