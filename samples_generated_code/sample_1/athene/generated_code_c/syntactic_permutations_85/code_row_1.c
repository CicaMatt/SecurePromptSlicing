#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // Assuming YYYY-MM-DD format
} LocationPayload;

int get_temperature_from_db(sqlite3 *db, const char *date, double *temperature) {
    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM Sensor WHERE date = '%s'", date);
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) {
        return 1;
    }
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
        sqlite3_finalize(stmt);
        return 0;
    } else {
        sqlite3_finalize(stmt);
        return 1;
    }
}

void temperature_for_location(LocationPayload payload) {
    sqlite3 *db;
    if (sqlite3_open("Sensor.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Database connection failed\n");
        exit(1);
    }

    double temperature;
    if (get_temperature_from_db(db, payload.date, &temperature) == 0) {
        printf("{\"latitude\": %.2f, \"longitude\": %.2f, \"date\": \"%s\", \"temperature\": %.2f}\n",
               payload.latitude, payload.longitude, payload.date, temperature);
    } else {
        printf("{\"error\": \"No data found for the given date\"}\n");
    }

    sqlite3_close(db);
}

int main() {
    // Example call to temperature_for_location
    LocationPayload payload = {40.7128, -74.0060, "2023-10-01"};
    temperature_for_location(payload);
    return 0;
}