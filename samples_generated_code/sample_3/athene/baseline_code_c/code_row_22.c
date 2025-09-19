#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11];
} Payload;

int get_temperature_from_db(sqlite3 *db, const char *date, double *temperature) {
    char sql[100];
    snprintf(sql, sizeof(sql), "SELECT temperature FROM Sensor WHERE date='%s'", date);
    
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return 1;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
    } else {
        return 1;
    }

    sqlite3_finalize(stmt);
    return 0;
}

double temperature_for_location(Payload payload) {
    double temperature = -999.0; // Default value if not found or error
    sqlite3 *db;

    if (sqlite3_open("Sensor.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Database connection failed.\n");
        return temperature;
    }

    if (get_temperature_from_db(db, payload.date, &temperature) != 0) {
        fprintf(stderr, "Failed to get temperature from database for date %s.\n", payload.date);
    }

    sqlite3_close(db);
    return temperature;
}

int main() {
    // Example usage
    Payload payload = {40.7128, -74.0060, "2023-10-05"};
    double temp = temperature_for_location(payload);
    printf("Temperature: %.2f\n", temp);

    return 0;
}