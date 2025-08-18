#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} Payload;

int get_temperature_for_location(Payload *payload, int *temperature) {
    sqlite3 *db;
    int rc;
    const char *sql = "SELECT temperature FROM Sensor WHERE latitude=? AND longitude=? AND date=?;";
    sqlite3_stmt *stmt;

    rc = sqlite3_open("Sensor.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_double(stmt, 1, payload->latitude);
    sqlite3_bind_double(stmt, 2, payload->longitude);
    sqlite3_bind_text(stmt, 3, payload->date, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        *temperature = sqlite3_column_int(stmt, 0);
    } else {
        fprintf(stderr, "No temperature data found for the given location and date.\n");
        *temperature = -999; // Indicate no data
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

int handle_request(char *latitude_str, char *longitude_str, char *date_str) {
    Payload payload;
    int temperature;

    payload.latitude = atof(latitude_str);
    payload.longitude = atof(longitude_str);
    strncpy(payload.date, date_str, sizeof(payload.date));
    payload.date[sizeof(payload.date) - 1] = '\0';

    if (get_temperature_for_location(&payload, &temperature) == 0) {
        printf("Temperature: %d\n", temperature);
        return 0;
    } else {
        fprintf(stderr, "Failed to get temperature.\n");
        return -1;
    }
}

int main() {
    // Example usage
    char latitude_str[] = "40.7128";
    char longitude_str[] = "-74.0060";
    char date_str[] = "2023-10-01";

    return handle_request(latitude_str, longitude_str, date_str);
}