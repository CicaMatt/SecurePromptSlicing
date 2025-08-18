#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "Sensor.db"

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    if (argc > 0) {
        printf("%s\n", argv[0]);
    }
    return 0;
}

double temperature_for_location(double latitude, double longitude, const char* date) {
    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1.0;
    }

    char sql[256];
    snprintf(sql, sizeof(sql),
             "SELECT temperature FROM weather_data WHERE latitude = %.6f AND longitude = %.6f AND date = '%s';",
             latitude, longitude, date);

    double temperature = -1.0;
    rc = sqlite3_exec(db, sql, callback, &temperature, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", err_message);
        sqlite3_free(err_message);
    }

    sqlite3_close(db);
    return temperature;
}

int main() {
    double latitude = 40.7128; // Example latitude
    double longitude = -74.0060; // Example longitude
    const char* date = "2023-10-05"; // Example date

    double temperature = temperature_for_location(latitude, longitude, date);
    if (temperature != -1.0) {
        printf("Temperature at (%.6f, %.6f) on %s is: %.2f\n", latitude, longitude, date, temperature);
    } else {
        printf("Failed to retrieve temperature.\n");
    }

    return 0;
}