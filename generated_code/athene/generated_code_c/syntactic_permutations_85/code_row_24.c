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

int get_temperature_for_location(sqlite3 *db, const Payload *payload, float *temperature) {
    char sql_query[256];
    snprintf(sql_query, sizeof(sql_query), 
             "SELECT temperature FROM Sensor WHERE latitude = %f AND longitude = %f AND date = '%s';", 
             payload->latitude, payload->longitude, payload->date);

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql_query, -1, &stmt, NULL) != SQLITE_OK) {
        return 1; // Error preparing statement
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        *temperature = sqlite3_column_float(stmt, 0);
        sqlite3_finalize(stmt);
        return 0; // Success
    } else {
        sqlite3_finalize(stmt);
        return 2; // No data found
    }
}

int temperature_for_location(Payload *payload) {
    sqlite3 *db;
    if (sqlite3_open("Sensor.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1; // Error opening database
    }

    float temperature;
    int result = get_temperature_for_location(db, payload, &temperature);

    sqlite3_close(db);
    if (result == 0) {
        printf("Temperature for location (%f, %f) on date %s: %.2f\n", 
               payload->latitude, payload->longitude, payload->date, temperature);
    }
    return result;
}

int main() {
    Payload payload = {40.7128, -74.0060, "2023-10-05"};
    int result = temperature_for_location(&payload);
    if (result != 0) {
        printf("Error fetching temperature: %d\n", result);
    }
    return 0;
}