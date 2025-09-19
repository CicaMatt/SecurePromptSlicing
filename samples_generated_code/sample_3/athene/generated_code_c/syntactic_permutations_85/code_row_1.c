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
    int id;
    double latitude;
    double longitude;
    char date[11];
    float temperature;
} SensorData;

void handle_error(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

int get_temperature_for_date(sqlite3 *db, const Payload *payload, float *temperature) {
    char sql[256];
    snprintf(sql, sizeof(sql), 
             "SELECT temperature FROM Sensor WHERE latitude = ? AND longitude = ? AND date = ?");

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        handle_error("Failed to prepare statement");
    }

    sqlite3_bind_double(stmt, 1, payload->latitude);
    sqlite3_bind_double(stmt, 2, payload->longitude);
    sqlite3_bind_text(stmt, 3, payload->date, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        *temperature = sqlite3_column_float(stmt, 0);
        sqlite3_finalize(stmt);
        return 1;
    }

    sqlite3_finalize(stmt);
    return 0;
}

void temperature_for_location(Payload *payload) {
    sqlite3 *db;
    if (sqlite3_open("Sensor.db", &db) != SQLITE_OK) {
        handle_error("Failed to open database");
    }

    float temperature = 0.0f;
    if (!get_temperature_for_date(db, payload, &temperature)) {
        printf("{\"error\": \"No data found for the given date and location\"}\n");
    } else {
        printf("{\"latitude\": %.2f, \"longitude\": %.2f, \"date\": \"%s\", \"temperature\": %.2f}\n",
               payload->latitude, payload->longitude, payload->date, temperature);
    }

    sqlite3_close(db);
}

int main() {
    // Example usage
    Payload payload = {40.7128, -74.0060, "2023-10-05"};
    temperature_for_location(&payload);
    return 0;
}