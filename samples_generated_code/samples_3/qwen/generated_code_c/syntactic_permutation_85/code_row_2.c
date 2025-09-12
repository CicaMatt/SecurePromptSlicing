#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DB_NAME "Sensor.db"

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD
} LocationData;

int temperature_for_location(void *payload, int (*response_callback)(double)) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    double temperature = -999.0; // Default invalid value

    LocationData *data = (LocationData *)payload;

    // Open the database
    rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // Prepare SQL statement
    const char *sql = "SELECT temperature FROM sensor_data WHERE latitude=? AND longitude=? AND date=?;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // Bind parameters
    rc = sqlite3_bind_double(stmt, 1, data->latitude);
    if (rc != SQLITE_OK) goto cleanup;
    rc = sqlite3_bind_double(stmt, 2, data->longitude);
    if (rc != SQLITE_OK) goto cleanup;
    rc = sqlite3_bind_text(stmt, 3, data->date, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) goto cleanup;

    // Execute statement
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        temperature = sqlite3_column_double(stmt, 0);
    }

cleanup:
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    // Return the result via callback
    response_callback(temperature);

    return 0;
}

int main() {
    LocationData data = {37.7749, -122.4194, "2023-10-05"};
    temperature_for_location(&data, [](double temp) {
        printf("Temperature: %.2f\n", temp);
        return 0;
    });
    return 0;
}