#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // Assuming date format is "YYYY-MM-DD"
} Payload;

double temperature_for_location(Payload *payload) {
    sqlite3 *db;
    char *err_msg = 0;
    int rc;
    double temperature = -999.9; // Default value in case of error

    rc = sqlite3_open("Sensor.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return temperature;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), 
             "SELECT temperature FROM SensorData WHERE latitude = %f AND longitude = %f AND date = '%s';",
             payload->latitude, payload->longitude, payload->date);

    rc = sqlite3_exec(db, sql, NULL, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return temperature;
    }

    sqlite3_stmt *stmt;
    const char *tail;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, &tail);
    if (rc == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            temperature = sqlite3_column_double(stmt, 0);
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return temperature;
}