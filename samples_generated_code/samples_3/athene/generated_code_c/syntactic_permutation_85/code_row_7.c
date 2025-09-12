#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} LocationData;

typedef struct {
    double temperature;
} TemperatureResponse;

int get_temperature_from_db(sqlite3 *db, const LocationData *data, TemperatureResponse *response) {
    char sql_query[256];
    sprintf(sql_query, "SELECT temperature FROM Sensor WHERE latitude = %f AND longitude = %f AND date = '%s'", data->latitude, data->longitude, data->date);
    
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql_query, -1, &stmt, NULL) != SQLITE_OK) {
        return 1; // Error preparing the statement
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        response->temperature = sqlite3_column_double(stmt, 0);
        sqlite3_finalize(stmt);
        return 0; // Success
    } else {
        sqlite3_finalize(stmt);
        return 2; // No data found
    }
}

int temperature_for_location(LocationData *data, TemperatureResponse *response) {
    sqlite3 *db;
    if (sqlite3_open("sensor.db", &db) != SQLITE_OK) {
        return 1; // Error opening the database
    }

    int result = get_temperature_from_db(db, data, response);

    sqlite3_close(db);
    return result;
}

int main() {
    LocationData location_data = {37.7749, -122.4194, "2023-10-01"};
    TemperatureResponse temperature_response;

    int result = temperature_for_location(&location_data, &temperature_response);

    if (result == 0) {
        printf("Temperature: %.2f\n", temperature_response.temperature);
    } else if (result == 1) {
        printf("Error opening database.\n");
    } else if (result == 2) {
        printf("No data found for the given location and date.\n");
    }

    return 0;
}