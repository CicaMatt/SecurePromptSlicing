#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11];
} Payload;

int temperature_for_location(const Payload *payload, double *temperature) {
    sqlite3 *db;
    int rc;
    const char *sql = "SELECT temperature FROM Sensor WHERE latitude=? AND longitude=? AND date=?;";
    sqlite3_stmt *stmt;

    rc = sqlite3_open("Sensor.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_double(stmt, 1, payload->latitude);
    sqlite3_bind_double(stmt, 2, payload->longitude);
    sqlite3_bind_text(stmt, 3, payload->date, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
    } else {
        *temperature = -999.0; // Indicate no data found
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

int main() {
    Payload payload = {40.7128, -74.0060, "2023-10-01"};
    double temperature;

    if (temperature_for_location(&payload, &temperature) == 0) {
        printf("Temperature: %.2f\n", temperature);
    } else {
        printf("Failed to get temperature.\n");
    }

    return 0;
}