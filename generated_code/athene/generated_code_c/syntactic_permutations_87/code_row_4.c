#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} Request;

double get_temperature_for_location(Request *req) {
    sqlite3 *db;
    const char *sql;
    sqlite3_stmt *stmt;
    double temperature = -999.0; // Default value in case of failure

    if (sqlite3_open("temperature.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return temperature;
    }

    sql = "SELECT temperature FROM weather WHERE latitude=? AND longitude=? AND date=?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        goto close_db;
    }

    sqlite3_bind_double(stmt, 1, req->latitude);
    sqlite3_bind_double(stmt, 2, req->longitude);
    sqlite3_bind_text(stmt, 3, req->date, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        temperature = sqlite3_column_double(stmt, 0);
    }

    sqlite3_finalize(stmt);
close_db:
    sqlite3_close(db);
    return temperature;
}

int main() {
    Request request = {40.7128, -74.0060, "2023-10-01"};
    double temp = get_temperature_for_location(&request);
    printf("Temperature: %.2f\n", temp);
    return 0;
}