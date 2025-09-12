#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_PAYLOAD_SIZE 256

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD
} Payload;

int parse_payload(const char *payload, Payload *parsed_payload) {
    return sscanf(payload, "latitude=%lf&longitude=%lf&date=%10s", 
                  &parsed_payload->latitude, &parsed_payload->longitude, parsed_payload->date);
}

double get_temperature_from_db(double latitude, double longitude, const char *date) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    double temperature = -999.0; // Default value if not found

    rc = sqlite3_open("Sensor.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return temperature;
    }

    const char *sql = "SELECT temperature FROM sensor_data WHERE latitude=? AND longitude=? AND date(reading_time)=?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return temperature;
    }

    sqlite3_bind_double(stmt, 1, latitude);
    sqlite3_bind_double(stmt, 2, longitude);
    sqlite3_bind_text(stmt, 3, date, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        temperature = sqlite3_column_double(stmt, 0);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return temperature;
}

double temperature_for_location(const char *payload) {
    Payload parsed_payload;

    if (parse_payload(payload, &parsed_payload) != 3) {
        fprintf(stderr, "Failed to parse payload\n");
        return -999.0; // Indicate error
    }

    return get_temperature_from_db(parsed_payload.latitude, parsed_payload.longitude, parsed_payload.date);
}

int main() {
    const char *payload = "latitude=37.7749&longitude=-122.4194&date=2023-10-05";
    double temperature = temperature_for_location(payload);

    if (temperature != -999.0) {
        printf("Temperature: %.2f\n", temperature);
    } else {
        printf("Failed to retrieve temperature\n");
    }

    return 0;
}