#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_PAYLOAD_SIZE 256

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD
} LocationData;

int temperature_for_location(LocationData *data, char **temperature) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_open("Sensor.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *sql = "SELECT temperature FROM sensor_data WHERE latitude = ? AND longitude = ? AND date = ?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
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
        *temperature = strdup((const char *)sqlite3_column_text(stmt, 0));
    } else {
        fprintf(stderr, "No data found\n");
        *temperature = NULL;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

int main() {
    LocationData data = {52.5200, 13.4050, "2023-10-01"};
    char *temperature;

    if (temperature_for_location(&data, &temperature) == 0 && temperature != NULL) {
        printf("Temperature: %s\n", temperature);
        free(temperature);
    } else {
        printf("Failed to retrieve temperature.\n");
    }

    return 0;
}