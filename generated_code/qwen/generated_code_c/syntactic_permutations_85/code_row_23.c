#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_QUERY_LENGTH 500

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD
} Payload;

double temperature_for_location(Payload payload) {
    sqlite3 *db;
    char *err_message = 0;
    int rc;
    sqlite3_stmt *stmt;
    double temperature = -999.0; // Default invalid value

    rc = sqlite3_open("Sensor.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return temperature;
    }

    char query[MAX_QUERY_LENGTH];
    snprintf(query, MAX_QUERY_LENGTH,
             "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?;");

    rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);

    if (rc == SQLITE_OK) {
        sqlite3_bind_double(stmt, 1, payload.latitude);
        sqlite3_bind_double(stmt, 2, payload.longitude);
        sqlite3_bind_text(stmt, 3, payload.date, -1, SQLITE_STATIC);

        rc = sqlite3_step(stmt);

        if (rc == SQLITE_ROW) {
            temperature = sqlite3_column_double(stmt, 0);
        }
    } else {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return temperature;
}

int main() {
    Payload payload = {40.7128, -74.0060, "2023-10-05"};
    double temp = temperature_for_location(payload);
    printf("Temperature: %.2f\n", temp);
    return 0;
}