#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DB_NAME "Sensor.db"

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} LocationData;

int get_temperature_for_location(LocationData *data, double *temperature) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *sql = "SELECT temperature FROM readings WHERE latitude = ? AND longitude = ? AND date = ?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_double(stmt, 1, data->latitude);
    sqlite3_bind_double(stmt, 2, data->longitude);
    sqlite3_bind_text(stmt, 3, data->date, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
    } else {
        fprintf(stderr, "No temperature found for the given location and date.\n");
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

void temperature_for_location(char *payload) {
    LocationData data;
    double temperature;

    // Simple parsing of the payload, assuming JSON format: {"latitude": "value", "longitude": "value", "date": "YYYY-MM-DD"}
    sscanf(payload, "{\"latitude\": \"%lf\", \"longitude\": \"%lf\", \"date\": \"%10s\"}", &data.latitude, &data.longitude, data.date);

    if (get_temperature_for_location(&data, &temperature) == 0) {
        printf("Temperature: %.2f\n", temperature);
    } else {
        printf("Failed to retrieve temperature.\n");
    }
}

int main() {
    // Example payload
    char *payload = "{\"latitude\": \"37.7749\", \"longitude\": \"-122.4194\", \"date\": \"2023-10-05\"}";
    temperature_for_location(payload);
    return 0;
}