#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    char *latitude;
    char *longitude;
    char *date;
} Request;

void temperature_for_location(Request *request) {
    sqlite3 *db;
    const char *sql = "SELECT temperature FROM weather_data WHERE latitude=? AND longitude=? AND date=?;";
    sqlite3_stmt *stmt;
    double temperature = 0.0;

    if (sqlite3_open("weather.db", &db)) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, request->latitude, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, request->longitude, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, request->date, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        temperature = sqlite3_column_double(stmt, 0);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    printf("Content-Type: application/json\n\n");
    printf("{\"temperature\": %.2f}\n", temperature);
}

int main() {
    Request request;
    char *latitude = getenv("QUERY_LATITUDE");
    char *longitude = getenv("QUERY_LONGITUDE");
    char *date = getenv("QUERY_DATE");

    if (latitude == NULL || longitude == NULL || date == NULL) {
        printf("Content-Type: application/json\n\n");
        printf("{\"error\": \"Missing parameters\"}\n");
        return 1;
    }

    request.latitude = latitude;
    request.longitude = longitude;
    request.date = date;

    temperature_for_location(&request);

    return 0;
}