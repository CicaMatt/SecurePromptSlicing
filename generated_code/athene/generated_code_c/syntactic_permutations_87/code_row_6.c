#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} Request;

typedef struct {
    double temperature;
} Response;

void handle_request(Request *req, Response *res) {
    sqlite3 *db;
    const char *sql;
    sqlite3_stmt *stmt;
    int rc;

    if (sqlite3_open("weather.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    sql = "SELECT temperature FROM weather_data WHERE latitude=? AND longitude=? AND date=?";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    sqlite3_bind_double(stmt, 1, req->latitude);
    sqlite3_bind_double(stmt, 2, req->longitude);
    sqlite3_bind_text(stmt, 3, req->date, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        res->temperature = sqlite3_column_double(stmt, 0);
    } else {
        fprintf(stderr, "No data found for the given coordinates and date.\n");
        res->temperature = -999.0; // Indicate no data
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    Request req = {40.7128, -74.0060, "2023-10-05"};
    Response res;

    handle_request(&req, &res);

    printf("Temperature: %.2f\n", res.temperature);
    return 0;
}