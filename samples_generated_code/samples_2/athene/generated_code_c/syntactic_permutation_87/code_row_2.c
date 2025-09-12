#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

void temperature_for_location(char* lat, char* lon, char* date) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    double temperature = 0.0;

    rc = sqlite3_open("weather.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    const char *sql = "SELECT temperature FROM weather_data WHERE latitude=? AND longitude=? AND date=?;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    sqlite3_bind_text(stmt, 1, lat, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, lon, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, date, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        temperature = sqlite3_column_double(stmt, 0);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    printf("Content-Type: text/plain\n\n");
    printf("%.2f", temperature);
}

int main() {
    char *lat = getenv("QUERY_LATITUDE");
    char *lon = getenv("QUERY_LONGITUDE");
    char *date = getenv("QUERY_DATE");

    if (lat && lon && date) {
        temperature_for_location(lat, lon, date);
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("Error: Missing parameters in request.");
    }

    return 0;
}