#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} Payload;

double getTemperature(sqlite3 *db, const char *date) {
    sqlite3_stmt *stmt;
    double temperature = -999.0; // Default to an invalid temperature

    const char *sql = "SELECT temperature FROM Sensor WHERE date = ?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, date, -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            temperature = sqlite3_column_double(stmt, 0);
        }
    }
    sqlite3_finalize(stmt);

    return temperature;
}

void handleApiRequest(Payload *payload) {
    sqlite3 *db;
    const char *dbName = "Sensor.db";

    if (sqlite3_open(dbName, &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    double temperature = getTemperature(db, payload->date);

    printf("{\"temperature\": %.2f}\n", temperature);

    sqlite3_close(db);
}

int main() {
    // Simulate receiving a payload from an HTTP request
    Payload payload = {40.7128, -74.0060, "2023-09-01"};
    handleApiRequest(&payload);
    return 0;
}