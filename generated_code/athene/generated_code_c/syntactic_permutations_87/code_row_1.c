#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11];
} LocationRequest;

typedef struct {
    float temperature;
} TemperatureResponse;

void get_request_params(LocationRequest *req) {
    // Simulate getting parameters from a request
    req->latitude = 37.7749; // Example value
    req->longitude = -122.4194; // Example value
    strcpy(req->date, "2023-10-05"); // Example value
}

int temperature_for_location() {
    sqlite3 *db;
    int rc;
    const char *sql;
    sqlite3_stmt *stmt;

    LocationRequest req;
    TemperatureResponse resp = { .temperature = 0.0 };

    get_request_params(&req);

    if (sqlite3_open("example.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    sql = "SELECT temperature FROM weather_data WHERE latitude=? AND longitude=? AND date=?;";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_double(stmt, 1, req.latitude);
    sqlite3_bind_double(stmt, 2, req.longitude);
    sqlite3_bind_text(stmt, 3, req.date, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        resp.temperature = sqlite3_column_float(stmt, 0);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    printf("Temperature: %.2f\n", resp.temperature);
    return 0;
}

int main() {
    temperature_for_location();
    return 0;
}