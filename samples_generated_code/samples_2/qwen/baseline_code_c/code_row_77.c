#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DB_NAME "weather_data.db"

int get_temperature_from_db(double latitude, double longitude, const char *date, double *temperature) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *query = "SELECT temperature FROM weather WHERE latitude=? AND longitude=? AND date=?";
    rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_double(stmt, 1, latitude);
    sqlite3_bind_double(stmt, 2, longitude);
    sqlite3_bind_text(stmt, 3, date, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
    } else if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to execute query: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return rc == SQLITE_ROW ? 0 : 1;
}

void temperature_for_location(double latitude, double longitude, const char *date) {
    double temperature;
    if (get_temperature_from_db(latitude, longitude, date, &temperature) == 0) {
        printf("Temperature: %.2f\n", temperature);
    } else {
        printf("Temperature data not found.\n");
    }
}

int main() {
    // Example usage
    double latitude = 40.7128;
    double longitude = -74.0060;
    const char *date = "2023-10-05";

    temperature_for_location(latitude, longitude, date);

    return 0;
}