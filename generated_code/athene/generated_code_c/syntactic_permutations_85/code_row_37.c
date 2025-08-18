#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} Payload;

void temperature_for_location(Payload *payload, int *temperature) {
    sqlite3 *db;
    const char *sql;
    sqlite3_stmt *stmt;
    char *errmsg;
    int rc;

    rc = sqlite3_open("example.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    sql = "SELECT temperature FROM weather_data WHERE latitude=? AND longitude=? AND date=?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    sqlite3_bind_double(stmt, 1, payload->latitude);
    sqlite3_bind_double(stmt, 2, payload->longitude);
    sqlite3_bind_text(stmt, 3, payload->date, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        *temperature = sqlite3_column_int(stmt, 0);
    } else {
        *temperature = -999; // Error or no data
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    Payload payload = {40.7128, -74.0060, "2023-01-01"};
    int temperature;

    temperature_for_location(&payload, &temperature);

    printf("Temperature: %d\n", temperature);

    return 0;
}