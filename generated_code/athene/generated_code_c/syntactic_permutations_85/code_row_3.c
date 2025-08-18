#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} Payload;

double get_temperature_from_db(sqlite3 *db, const char *date) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT temperature FROM Sensor WHERE date = ?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "SQL Error: %s\n", sqlite3_errmsg(db));
        return 0.0;
    }

    sqlite3_bind_text(stmt, 1, date, -1, SQLITE_STATIC);

    double temperature = 0.0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        temperature = sqlite3_column_double(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return temperature;
}

double temperature_for_location(Payload *payload) {
    sqlite3 *db;
    int rc = sqlite3_open("Sensor.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    double temperature = get_temperature_from_db(db, payload->date);

    sqlite3_close(db);
    return temperature;
}

int main() {
    Payload payload = {40.7128, -74.0060, "2023-10-05"};
    double temp = temperature_for_location(&payload);
    printf("Temperature: %.2f\n", temp);
    return 0;
}