#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
} Payload;

int get_temperature_from_db(sqlite3 *db, double latitude, double longitude, double *temperature) {
    char sql[1024];
    sprintf(sql, "SELECT temperature FROM Sensor WHERE latitude = %f AND longitude = %f", latitude, longitude);
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return 1;
    }
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
        sqlite3_finalize(stmt);
        return 0;
    } else {
        sqlite3_finalize(stmt);
        return 1;
    }
}

void temperature_for_location(Payload *payload, double *temperature) {
    sqlite3 *db;
    if (sqlite3_open("Sensor.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    if (get_temperature_from_db(db, payload->latitude, payload->longitude, temperature) != 0) {
        *temperature = -999; // Indicate error
    }
    sqlite3_close(db);
}

int main() {
    Payload payload = {37.7749, -122.4194}; // Example coordinates for San Francisco
    double temperature;
    temperature_for_location(&payload, &temperature);
    if (temperature != -999) {
        printf("Temperature: %.2f\n", temperature);
    } else {
        printf("Temperature not found.\n");
    }
    return 0;
}