#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD
} Payload;

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

double temperature_for_location(Payload payload) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    double temperature = -999.0; // Default value indicating an error

    rc = sqlite3_open("Sensor.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return temperature;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), 
             "SELECT temperature FROM weather_data WHERE latitude = %.6f AND longitude = %.6f AND date = '%s';",
             payload.latitude, payload.longitude, payload.date);

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc == SQLITE_ROW) {
        sqlite3_stmt *stmt;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                temperature = sqlite3_column_double(stmt, 0);
            }
            sqlite3_finalize(stmt);
        }
    } else if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    sqlite3_close(db);
    return temperature;
}

int main() {
    Payload payload = {52.5200, 13.4050, "2023-10-01"}; // Example: Berlin, Germany on October 1, 2023
    double temp = temperature_for_location(payload);
    if (temp != -999.0) {
        printf("Temperature: %.2f\n", temp);
    } else {
        printf("Failed to retrieve temperature.\n");
    }
    return 0;
}