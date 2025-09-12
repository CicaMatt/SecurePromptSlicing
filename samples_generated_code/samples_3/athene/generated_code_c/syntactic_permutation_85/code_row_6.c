#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11];
} Payload;

typedef struct {
    float temperature;
} TemperatureResponse;

void get_temperature_from_db(sqlite3 *db, const char *date, float *temperature) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT temperature FROM Sensor WHERE date = ? LIMIT 1;";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement\n");
        return;
    }

    sqlite3_bind_text(stmt, 1, date, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        *temperature = sqlite3_column_float(stmt, 0);
    } else {
        *temperature = -999.0; // Indicate no data found
    }

    sqlite3_finalize(stmt);
}

TemperatureResponse temperature_for_location(Payload *payload) {
    TemperatureResponse response;
    sqlite3 *db;
    int rc;

    rc = sqlite3_open("sensor.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        response.temperature = -999.0; // Indicate error
        return response;
    }

    get_temperature_from_db(db, payload->date, &response.temperature);

    sqlite3_close(db);
    return response;
}

int main() {
    Payload payload = {40.7128, -74.0060, "2023-10-05"};
    TemperatureResponse response = temperature_for_location(&payload);
    printf("Temperature: %.2f\n", response.temperature);
    return 0;
}