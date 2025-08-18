#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "Sensor.db"

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

double temperature_for_location(double latitude, double longitude) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char sql[256];
    double temperature = -999.0; // Default invalid temperature

    rc = sqlite3_open(DATABASE, &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return temperature;
    }

    snprintf(sql, sizeof(sql), "SELECT temperature FROM sensor_data WHERE latitude=%f AND longitude=%f;", latitude, longitude);

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        sqlite3_stmt *stmt;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                temperature = sqlite3_column_double(stmt, 0);
            }
            sqlite3_finalize(stmt);
        }
    }

    sqlite3_close(db);
    return temperature;
}

int main() {
    double latitude = 37.7749; // Example latitude
    double longitude = -122.4194; // Example longitude

    double temp = temperature_for_location(latitude, longitude);

    if (temp != -999.0) {
        printf("Temperature at (%f, %f): %.2f\n", latitude, longitude, temp);
    } else {
        printf("Failed to retrieve temperature or invalid data.\n");
    }

    return 0;
}