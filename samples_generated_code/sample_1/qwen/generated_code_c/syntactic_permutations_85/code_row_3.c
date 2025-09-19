#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "Sensor.db"

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

double temperature_for_location(double latitude, double longitude, const char *date) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    double temperature = -999.0; // Default value indicating error

    rc = sqlite3_open(DATABASE, &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return temperature;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), 
             "SELECT temperature FROM sensor_data WHERE latitude = %.6f AND longitude = %.6f AND date = '%s';",
             latitude, longitude, date);

    rc = sqlite3_exec(db, sql, callback, &temperature, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        // Assuming the first row returned is the correct one
        char *query = malloc(strlen(sql) + 100);
        snprintf(query, strlen(sql) + 100, 
                 "SELECT temperature FROM sensor_data WHERE latitude = %.6f AND longitude = %.6f AND date = '%s';",
                 latitude, longitude, date);

        sqlite3_stmt *stmt;
        rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
        if (rc == SQLITE_OK) {
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                temperature = sqlite3_column_double(stmt, 0);
            }
        } else {
            fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        }

        sqlite3_finalize(stmt);
        free(query);
    }

    sqlite3_close(db);

    return temperature;
}

int main() {
    double latitude = 40.7128;
    double longitude = -74.0060;
    const char *date = "2023-10-01";

    double temp = temperature_for_location(latitude, longitude, date);
    if (temp != -999.0) {
        printf("Temperature: %.2f\n", temp);
    } else {
        printf("Failed to retrieve temperature.\n");
    }

    return 0;
}