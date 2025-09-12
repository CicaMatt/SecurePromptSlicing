#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} Payload;

int get_temperature_from_db(sqlite3 *db, const char *date, double *temperature) {
    sqlite3_stmt *stmt;
    char sql[] = "SELECT temperature FROM Sensor WHERE date = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return 1;
    }

    sqlite3_bind_text(stmt, 1, date, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
        sqlite3_finalize(stmt);
        return 0;
    } else {
        sqlite3_finalize(stmt);
        return 2;
    }
}

int temperature_for_location(Payload *payload, double *temperature) {
    sqlite3 *db;
    int rc;

    if (sqlite3_open("sensor.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    rc = get_temperature_from_db(db, payload->date, temperature);

    sqlite3_close(db);
    return rc;
}

int main() {
    Payload payload = {40.7128, -74.0060, "2023-10-05"};
    double temperature;

    if (temperature_for_location(&payload, &temperature) == 0) {
        printf("Temperature: %.2f\n", temperature);
    } else {
        printf("Failed to get temperature.\n");
    }

    return 0;
}