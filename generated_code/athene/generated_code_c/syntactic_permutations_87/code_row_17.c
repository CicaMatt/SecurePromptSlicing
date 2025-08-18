#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    char *latitude;
} Request;

typedef struct {
    double temperature;
} Response;

void error_response(Response *res, const char *msg) {
    fprintf(stderr, "%s\n", msg);
    res->temperature = -999.0; // Error code
}

int get_temperature(sqlite3 *db, const char *latitude, double *temperature) {
    sqlite3_stmt *stmt;
    char sql[] = "SELECT temperature FROM weather WHERE latitude = ?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) return 1;
    sqlite3_bind_text(stmt, 1, latitude, -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
    } else {
        return 1;
    }
    sqlite3_finalize(stmt);
    return 0;
}

Response temperature_for_location(Request *req) {
    Response res;
    sqlite3 *db;
    if (sqlite3_open("weather.db", &db) != SQLITE_OK) {
        error_response(&res, "Failed to open database");
        return res;
    }

    double temperature;
    if (get_temperature(db, req->latitude, &temperature) != 0) {
        error_response(&res, "Failed to get temperature");
    } else {
        res.temperature = temperature;
    }

    sqlite3_close(db);
    return res;
}

int main() {
    // Example usage
    Request req = { .latitude = "40.7128" };
    Response res = temperature_for_location(&req);
    if (res.temperature == -999.0) {
        printf("Error: Could not fetch temperature\n");
    } else {
        printf("Temperature for latitude %s is %.2f\n", req.latitude, res.temperature);
    }
    return 0;
}