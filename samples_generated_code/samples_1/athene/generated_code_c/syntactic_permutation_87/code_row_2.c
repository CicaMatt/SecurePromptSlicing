#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_QUERY_LENGTH 256

typedef struct {
    char *latitude;
    char *longitude;
    char *date;
} Request;

void get_request_params(Request *req, const char *query) {
    sscanf(query, "lat=%[^&]&lon=%[^&]&date=%s", req->latitude, req->longitude, req->date);
}

int temperature_for_location(const char *query, float *temperature) {
    sqlite3 *db;
    int rc;

    Request req = { .latitude = malloc(20), .longitude = malloc(20), .date = malloc(20) };
    get_request_params(&req, query);

    const char *sql = "SELECT temperature FROM weather_data WHERE latitude=? AND longitude=? AND date=?;";

    rc = sqlite3_open("weather.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, req.latitude, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, req.longitude, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, req.date, -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
    } else {
        fprintf(stderr, "No temperature data found for the given location and date.\n");
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        free(req.latitude);
        free(req.longitude);
        free(req.date);
        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    free(req.latitude);
    free(req.longitude);
    free(req.date);

    return 0;
}

int main() {
    float temperature;
    const char *query = "lat=37.7749&lon=-122.4194&date=2023-10-05";
    if (temperature_for_location(query, &temperature) == 0) {
        printf("Temperature: %.2f\n", temperature);
    } else {
        printf("Failed to get temperature.\n");
    }
    return 0;
}