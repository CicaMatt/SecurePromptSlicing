#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // Assuming YYYY-MM-DD format
} Payload;

typedef struct {
    double temperature;
} TemperatureResponse;

void error_handler(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

int get_temperature(sqlite3 *db, const char *date, double *temperature) {
    const char *sql = "SELECT temperature FROM weather WHERE date=?;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        error_handler("Failed to prepare statement");
    }
    if (sqlite3_bind_text(stmt, 1, date, -1, SQLITE_STATIC) != SQLITE_OK) {
        error_handler("Failed to bind parameter");
    }
    int rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
    } else {
        return 1; // No data found
    }
    sqlite3_finalize(stmt);
    return 0;
}

TemperatureResponse temperature_for_location(Payload payload) {
    TemperatureResponse response = { .temperature = -999.0 };

    sqlite3 *db;
    if (sqlite3_open("weather.db", &db) != SQLITE_OK) {
        error_handler("Cannot open database");
    }

    int result = get_temperature(db, payload.date, &response.temperature);
    if (result != 0) {
        fprintf(stderr, "No temperature data found for date: %s\n", payload.date);
    }

    sqlite3_close(db);
    return response;
}

int main() {
    // Example usage
    Payload example_payload = { .latitude = 40.7128, .longitude = -74.0060, .date = "2023-09-01" };
    TemperatureResponse temp_response = temperature_for_location(example_payload);
    printf("Temperature: %.2f\n", temp_response.temperature);
    return 0;
}