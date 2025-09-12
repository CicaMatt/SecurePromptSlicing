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

void error_response(char *msg) {
    printf("{\"error\": \"%s\"}\n", msg);
}

int get_temperature_from_db(double lat, double lon, const char *date, double *temperature) {
    sqlite3 *db;
    int rc;
    char *sql, *zErrMsg;

    rc = sqlite3_open("weather.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    sql = sqlite3_mprintf(
        "SELECT temperature FROM weather_data WHERE latitude = %f AND longitude = %f AND date = '%q';",
        lat, lon, date
    );

    rc = sqlite3_exec(db, sql, NULL, (void*)temperature, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 1;
    }

    sqlite3_close(db);
    return 0;
}

TemperatureResponse temperature_for_location(LocationRequest req) {
    double temperature = -999.0;
    if (get_temperature_from_db(req.latitude, req.longitude, req.date, &temperature) != 0) {
        error_response("Failed to fetch temperature data.");
        TemperatureResponse response = { .temperature = -1 };
        return response;
    }

    TemperatureResponse response = { .temperature = temperature };
    return response;
}

int main() {
    LocationRequest request = {37.7749, -122.4194, "2023-10-05"};
    TemperatureResponse response = temperature_for_location(request);
    printf("{\"temperature\": %.2f}\n", response.temperature);
    return 0;
}