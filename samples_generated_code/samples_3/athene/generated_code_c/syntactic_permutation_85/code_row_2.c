#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} Payload;

int get_temperature_from_db(double latitude, double longitude, const char *date, double *temperature) {
    sqlite3 *db;
    int rc;
    char sql[256];
    
    rc = sqlite3_open("Sensor.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    snprintf(sql, sizeof(sql), 
             "SELECT temperature FROM Sensor WHERE latitude=%f AND longitude=%f AND date='%s'", 
             latitude, longitude, date);

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
    } else {
        *temperature = -999; // Indicate no data found
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

int temperature_for_location(Payload payload, double *temperature) {
    return get_temperature_from_db(payload.latitude, payload.longitude, payload.date, temperature);
}

// Example usage (not part of the API handler)
int main() {
    Payload payload = {40.7128, -74.0060, "2023-10-05"};
    double temperature;
    
    if (temperature_for_location(payload, &temperature) == 0) {
        printf("Temperature: %.2f\n", temperature);
    } else {
        printf("Failed to get temperature.\n");
    }

    return 0;
}