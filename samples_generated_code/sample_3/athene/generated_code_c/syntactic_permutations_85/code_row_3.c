#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11];
} Payload;

typedef struct {
    double temperature;
} TemperatureResponse;

void handle_error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int get_temperature(sqlite3 *db, const char *date, double *temperature) {
    sqlite3_stmt *stmt;
    char sql[] = "SELECT temperature FROM Sensor WHERE date = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_bind_text(stmt, 1, date, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
    } else {
        fprintf(stderr, "No temperature found for the given date.\n");
        return 1;
    }

    sqlite3_finalize(stmt);
    return 0;
}

TemperatureResponse temperature_for_location(Payload payload) {
    TemperatureResponse response;

    sqlite3 *db;
    if (sqlite3_open("Sensor.db", &db)) {
        handle_error("Can't open database");
    }

    double temperature;
    if (get_temperature(db, payload.date, &temperature) == 0) {
        response.temperature = temperature;
    } else {
        response.temperature = -999.9; // Error value
    }

    sqlite3_close(db);
    return response;
}

int main() {
    Payload payload = {40.7128, -74.0060, "2023-10-01"};
    TemperatureResponse response = temperature_for_location(payload);

    printf("Temperature: %.2f\n", response.temperature);
    return 0;
}