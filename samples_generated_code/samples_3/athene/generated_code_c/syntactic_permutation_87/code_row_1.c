#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    char *latitude;
    char *longitude;
    char *date;
} Request;

int get_temperature_from_db(sqlite3 *db, const char *latitude, const char *longitude, const char *date, double *temperature) {
    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT temperature FROM weather_data WHERE latitude = '%s' AND longitude = '%s' AND date = '%s';", latitude, longitude, date);
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return 1;
    }
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
        sqlite3_finalize(stmt);
        return 0;
    }
    sqlite3_finalize(stmt);
    return 1;
}

double temperature_for_location(Request *req) {
    double temperature = -999.9; // Default value indicating failure
    sqlite3 *db;
    if (sqlite3_open("weather.db", &db) != SQLITE_OK) {
        return temperature;
    }

    if (get_temperature_from_db(db, req->latitude, req->longitude, req->date, &temperature) == 0) {
        sqlite3_close(db);
        return temperature;
    }

    sqlite3_close(db);
    return -999.9; // Indicate failure
}

int main() {
    Request request = {"37.7749", "-122.4194", "2023-10-05"};
    double temperature = temperature_for_location(&request);
    if (temperature != -999.9) {
        printf("Temperature: %.2f\n", temperature);
    } else {
        printf("Failed to get temperature.\n");
    }
    return 0;
}