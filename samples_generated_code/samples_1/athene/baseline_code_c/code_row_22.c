#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11];
} Payload;

typedef struct {
    double temperature;
} TemperatureResponse;

int get_temperature_from_db(sqlite3 *db, const char *date, double *temperature) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT temperature FROM Sensor WHERE date = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) return 1;

    sqlite3_bind_text(stmt, 1, date, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
        sqlite3_finalize(stmt);
        return 0;
    }

    sqlite3_finalize(stmt);
    return 1;
}

TemperatureResponse temperature_for_location(Payload payload) {
    TemperatureResponse response;
    sqlite3 *db;
    double temperature = 0.0;

    if (sqlite3_open("Sensor.db", &db) != SQLITE_OK) {
        response.temperature = -9999; // Error code for database failure
        return response;
    }

    if (get_temperature_from_db(db, payload.date, &temperature) == 0) {
        response.temperature = temperature;
    } else {
        response.temperature = -9998; // Error code for no data found
    }

    sqlite3_close(db);
    return response;
}

int main() {
    Payload payload = {40.7128, -74.0060, "2023-10-05"};
    TemperatureResponse response = temperature_for_location(payload);

    printf("Temperature: %.2f\n", response.temperature);
    return 0;
}