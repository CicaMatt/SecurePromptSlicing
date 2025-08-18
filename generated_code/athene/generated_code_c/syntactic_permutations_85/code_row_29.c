#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} LocationPayload;

typedef struct {
    double temperature;
} TemperatureResponse;

void get_temperature_from_db(sqlite3 *db, const char *date, double *temperature) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT temperature FROM Sensor WHERE date = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, date, -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            *temperature = sqlite3_column_double(stmt, 0);
        }
    }
    sqlite3_finalize(stmt);
}

TemperatureResponse temperature_for_location(LocationPayload payload) {
    TemperatureResponse response;
    sqlite3 *db;
    char *err_msg = NULL;

    if (sqlite3_open("sensor.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    get_temperature_from_db(db, payload.date, &response.temperature);

    sqlite3_close(db);
    return response;
}

int main() {
    // Example usage
    LocationPayload payload = {40.7128, -74.0060, "2023-09-01"};
    TemperatureResponse response = temperature_for_location(payload);

    printf("Temperature: %.2f\n", response.temperature);
    return 0;
}