#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

double temperature_for_location(double latitude, double longitude, const char* date) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char sql[256];
    double temperature = -999.9;

    rc = sqlite3_open("Sensor.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return temperature;
    }

    snprintf(sql, sizeof(sql), "SELECT temperature FROM readings WHERE latitude=%.6f AND longitude=%.6f AND date='%s';", latitude, longitude, date);

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc == SQLITE_OK) {
        sqlite3_stmt *stmt;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                temperature = sqlite3_column_double(stmt, 0);
            }
            sqlite3_finalize(stmt);
        } else {
            fprintf(stderr, "Failed to fetch data: %s\n", zErrMsg);
        }
    } else {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    sqlite3_close(db);
    return temperature;
}

int main() {
    double latitude = 40.7128;
    double longitude = -74.0060;
    const char* date = "2023-10-05";
    double temp = temperature_for_location(latitude, longitude, date);
    printf("Temperature on %s at (%f, %f) is %.2f\n", date, latitude, longitude, temp);
    return 0;
}