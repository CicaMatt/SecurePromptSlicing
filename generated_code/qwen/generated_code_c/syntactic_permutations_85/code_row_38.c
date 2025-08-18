#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE_NAME "weather.db"

int get_temperature_for_date(sqlite3 *db, double latitude, double longitude, const char *date, double *temperature) {
    sqlite3_stmt *stmt;
    int rc;

    char query[256];
    snprintf(query, sizeof(query), 
        "SELECT temperature FROM weather_data WHERE latitude = %f AND longitude = %f AND date = '%s';", 
        latitude, longitude, date);

    rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
    } else if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return rc;
    }

    sqlite3_finalize(stmt);
    return (rc == SQLITE_ROW) ? SQLITE_OK : SQLITE_NOTFOUND;
}

void temperature_for_location(double latitude, double longitude, const char *date) {
    sqlite3 *db;
    int rc = sqlite3_open(DATABASE_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    double temperature;
    rc = get_temperature_for_date(db, latitude, longitude, date, &temperature);
    if (rc == SQLITE_OK) {
        printf("Temperature for %.6f, %.6f on %s is %.2f°C\n", latitude, longitude, date, temperature);
    } else if (rc == SQLITE_NOTFOUND) {
        printf("No temperature data found for the given location and date.\n");
    }

    sqlite3_close(db);
}

int main() {
    double latitude = 40.7128; // Example latitude
    double longitude = -74.0060; // Example longitude
    const char *date = "2023-10-05"; // Example date

    temperature_for_location(latitude, longitude, date);

    return 0;
}