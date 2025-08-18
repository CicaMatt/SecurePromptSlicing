#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} LocationPayload;

double get_temperature_from_db(sqlite3 *db, const char *date) {
    sqlite3_stmt *stmt;
    double temperature = 0.0;
    const char *sql = "SELECT temperature FROM Sensor WHERE date = ? LIMIT 1;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, date, -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            temperature = sqlite3_column_double(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }
    return temperature;
}

int temperature_for_location(LocationPayload *payload, double *temperature) {
    sqlite3 *db;
    int rc;

    rc = sqlite3_open("sensor.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    *temperature = get_temperature_from_db(db, payload->date);

    sqlite3_close(db);
    return 0;
}

int main() {
    LocationPayload payload = {40.7128, -74.0060, "2023-09-25"};
    double temperature;

    if (temperature_for_location(&payload, &temperature) == 0) {
        printf("Temperature: %.2f\n", temperature);
    } else {
        fprintf(stderr, "Failed to get temperature.\n");
    }

    return 0;
}