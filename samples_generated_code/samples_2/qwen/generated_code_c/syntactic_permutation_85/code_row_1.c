#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD
} Payload;

double temperature_for_location(Payload payload) {
    sqlite3 *db;
    int rc;
    char *err_message = 0;
    sqlite3_stmt *res;
    double temperature = -999.0; // Default value indicating error

    rc = sqlite3_open("Sensor.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return temperature;
    }

    char query[256];
    snprintf(query, sizeof(query),
             "SELECT temperature FROM sensor_data WHERE latitude = %.6f AND longitude = %.6f AND date = '%s';",
             payload.latitude, payload.longitude, payload.date);

    rc = sqlite3_prepare_v2(db, query, -1, &res, 0);
    if (rc == SQLITE_OK) {
        if (sqlite3_step(res) == SQLITE_ROW) {
            temperature = sqlite3_column_double(res, 0);
        }
    } else {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(res);
    sqlite3_close(db);

    return temperature;
}

int main() {
    Payload payload = {40.7128, -74.0060, "2023-10-01"};
    double temp = temperature_for_location(payload);
    if (temp != -999.0) {
        printf("Temperature: %.2f\n", temp);
    } else {
        printf("Failed to retrieve temperature.\n");
    }
    return 0;
}