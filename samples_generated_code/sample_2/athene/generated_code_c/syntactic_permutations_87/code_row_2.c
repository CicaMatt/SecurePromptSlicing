#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11];
} LocationRequest;

typedef struct {
    double temperature;
} TemperatureResponse;

int get_temperature(sqlite3 *db, const LocationRequest *request, TemperatureResponse *response) {
    char sql_query[256];
    snprintf(sql_query, sizeof(sql_query), 
             "SELECT temperature FROM weather_data WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             request->latitude, request->longitude, request->date);

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql_query, -1, &stmt, NULL) != SQLITE_OK) {
        return 1; // Error preparing the query
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        response->temperature = sqlite3_column_double(stmt, 0);
    } else {
        response->temperature = -999.0; // No data found
    }

    sqlite3_finalize(stmt);
    return 0;
}

int temperature_for_location(LocationRequest *request, TemperatureResponse *response) {
    sqlite3 *db;
    if (sqlite3_open("weather.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    int result = get_temperature(db, request, response);

    sqlite3_close(db);
    return result;
}

int main() {
    // Example usage
    LocationRequest req = {37.7749, -122.4194, "2023-10-05"};
    TemperatureResponse res;

    if (temperature_for_location(&req, &res) == 0) {
        printf("Temperature: %.2f\n", res.temperature);
    } else {
        printf("Failed to get temperature.\n");
    }

    return 0;
}