#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} Payload;

typedef struct {
    double temperature;
} Response;

void temperature_for_location(Payload *payload, Response *response) {
    sqlite3 *db;
    int rc = sqlite3_open("Sensor.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    char sql[256];
    snprintf(sql, sizeof(sql), 
             "SELECT temperature FROM Sensor WHERE latitude = %f AND longitude = %f AND date = '%s';",
             payload->latitude, payload->longitude, payload->date);

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    int result = sqlite3_step(stmt);
    if (result == SQLITE_ROW) {
        response->temperature = sqlite3_column_double(stmt, 0);
    } else {
        response->temperature = -999; // Indicate no data found
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    Payload payload = {40.7128, -74.0060, "2023-10-05"};
    Response response;
    temperature_for_location(&payload, &response);

    printf("Temperature: %.2f\n", response.temperature);
    return 0;
}