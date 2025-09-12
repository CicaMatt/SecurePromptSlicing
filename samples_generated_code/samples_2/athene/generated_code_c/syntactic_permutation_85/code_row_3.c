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

void handle_error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int get_temperature(sqlite3 *db, const Payload *payload, Response *response) {
    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM Sensor WHERE latitude = %f AND longitude = %f AND date = '%s'",
             payload->latitude, payload->longitude, payload->date);

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        response->temperature = sqlite3_column_double(stmt, 0);
    } else {
        fprintf(stderr, "No data found for the given location and date.\n");
        return 1;
    }

    sqlite3_finalize(stmt);
    return 0;
}

void temperature_for_location(Payload *payload, Response *response) {
    sqlite3 *db;
    if (sqlite3_open("Sensor.db", &db) != SQLITE_OK) {
        handle_error("Failed to open database");
    }

    int result = get_temperature(db, payload, response);

    sqlite3_close(db);
    if (result != 0) {
        handle_error("Failed to get temperature");
    }
}

int main() {
    // Example usage
    Payload payload = {40.7128, -74.0060, "2023-10-01"};
    Response response;

    temperature_for_location(&payload, &response);

    printf("Temperature: %.2f\n", response.temperature);
    return 0;
}