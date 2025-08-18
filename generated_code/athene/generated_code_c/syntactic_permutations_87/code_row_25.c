#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} LocationRequest;

double get_temperature_from_db(double lat, double lon, const char *date) {
    sqlite3 *db;
    int rc;
    double temperature = 0.0;

    rc = sqlite3_open("weather.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1.0;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT temperature FROM weather_data WHERE latitude = %f AND longitude = %f AND date = '%s'", lat, lon, date);

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1.0;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        temperature = sqlite3_column_double(stmt, 0);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return temperature;
}

double temperature_for_location(LocationRequest *request) {
    double latitude = request->latitude;
    double longitude = request->longitude;
    char date[11];
    strncpy(date, request->date, sizeof(date));
    date[sizeof(date) - 1] = '\0';

    return get_temperature_from_db(latitude, longitude, date);
}

int main() {
    // Example usage
    LocationRequest req = {37.7749, -122.4194, "2023-01-01"};
    double temperature = temperature_for_location(&req);
    printf("Temperature: %.2f\n", temperature);

    return 0;
}