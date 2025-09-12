#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} Payload;

double temperature_for_location(Payload *payload) {
    sqlite3 *db;
    int rc;
    const char *sql;
    char *err_msg = 0;
    double temperature = -999.0; // Default value in case of error

    // Open database
    rc = sqlite3_open("Sensor.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return temperature;
    }

    // Prepare SQL query
    sql = "SELECT temperature FROM Sensor WHERE latitude=? AND longitude=? AND date=?;";

    sqlite3_stmt *res;
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return temperature;
    }

    // Bind parameters
    sqlite3_bind_double(res, 1, payload->latitude);
    sqlite3_bind_double(res, 2, payload->longitude);
    sqlite3_bind_text(res, 3, payload->date, -1, SQLITE_STATIC);

    // Execute the query
    if (sqlite3_step(res) == SQLITE_ROW) {
        temperature = sqlite3_column_double(res, 0);
    } else {
        fprintf(stderr, "No data found for the given location and date.\n");
    }

    // Finalize statement and close database
    sqlite3_finalize(res);
    sqlite3_close(db);

    return temperature;
}

int main() {
    Payload payload = {40.7128, -74.0060, "2023-10-05"};
    double temp = temperature_for_location(&payload);
    printf("Temperature: %.2f\n", temp);
    return 0;
}