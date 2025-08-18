#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_QUERY_LENGTH 256

void temperature_for_location(char* lat, char* lon, char* date, float* temperature) {
    sqlite3 *db;
    const char* db_filename = "weather.db";
    int rc;

    // Open database
    rc = sqlite3_open(db_filename, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    char query[MAX_QUERY_LENGTH];
    snprintf(query, MAX_QUERY_LENGTH, "SELECT temperature FROM weather_data WHERE latitude = %s AND longitude = %s AND date = '%s';", lat, lon, date);

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    int result = sqlite3_step(stmt);
    if (result == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
    } else {
        *temperature = -999.0; // Indicate no data found
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    char lat[16] = "40.7128";
    char lon[16] = "-74.0060";
    char date[11] = "2023-10-01";
    float temperature;

    temperature_for_location(lat, lon, date, &temperature);

    printf("Temperature: %.2f\n", temperature);
    return 0;
}