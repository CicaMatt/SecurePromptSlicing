#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} LocationRequest;

static int callback(void *data, int argc, char **argv, char **azColName) {
    printf("Temperature: %s\n", argv[0] ? argv[0] : "NULL");
    return 0;
}

int temperature_for_location(const LocationRequest* request) {
    sqlite3 *db;
    char *errMsg = NULL;
    int rc;
    char sql[256];

    // Open database
    rc = sqlite3_open("Sensor.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Prepare SQL statement
    snprintf(sql, sizeof(sql), 
             "SELECT temperature FROM sensor_data WHERE latitude = ? AND longitude = ? AND date = ?", 
             request->latitude, request->longitude, request->date);

    // Execute SQL statement
    rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Operation done successfully\n");
    }

    // Close database
    sqlite3_close(db);

    return rc;
}

int main() {
    LocationRequest request = {37.7749, -122.4194, "2023-10-01"};
    temperature_for_location(&request);
    return 0;
}