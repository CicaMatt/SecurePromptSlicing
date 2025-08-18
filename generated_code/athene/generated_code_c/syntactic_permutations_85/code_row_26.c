#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[12];
} Payload;

void temperature_for_location(Payload *payload) {
    sqlite3 *db;
    int rc;
    const char *sql;
    double temperature = 0.0;
    char *zErrMsg = NULL;

    // Open database
    rc = sqlite3_open("Sensor.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sql = "SELECT temperature FROM Sensor WHERE latitude=? AND longitude=? AND date=?";

    rc = sqlite3_exec(db, sql, NULL, payload, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return;
    }

    sqlite3_stmt *res;
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_double(res, 1, payload->latitude);
        sqlite3_bind_double(res, 2, payload->longitude);
        sqlite3_bind_text(res, 3, payload->date, -1, SQLITE_STATIC);

        while (sqlite3_step(res) == SQLITE_ROW) {
            temperature = sqlite3_column_double(res, 0);
        }
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    // Clean up
    sqlite3_finalize(res);
    sqlite3_close(db);

    printf("Temperature: %.2f\n", temperature);
}

int main() {
    Payload payload = {40.7128, -74.0060, "2023-10-01"};
    temperature_for_location(&payload);
    return 0;
}