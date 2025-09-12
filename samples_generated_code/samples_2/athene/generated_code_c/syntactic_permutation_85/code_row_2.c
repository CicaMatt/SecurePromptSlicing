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
    float temperature;
} TemperatureResponse;

void temperature_for_location(Payload *payload, TemperatureResponse *response) {
    sqlite3 *db;
    int rc;
    const char *sql = "SELECT temperature FROM Sensor WHERE latitude=? AND longitude=? AND date=?;";
    sqlite3_stmt *stmt;

    rc = sqlite3_open("Sensor.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    sqlite3_bind_double(stmt, 1, payload->latitude);
    sqlite3_bind_double(stmt, 2, payload->longitude);
    sqlite3_bind_text(stmt, 3, payload->date, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        response->temperature = sqlite3_column_float(stmt, 0);
    } else {
        response->temperature = -999.0; // Indicate no data found
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    Payload payload = {37.7749, -122.4194, "2023-10-01"};
    TemperatureResponse response;

    temperature_for_location(&payload, &response);

    printf("Temperature: %.2f\n", response.temperature);
    return 0;
}