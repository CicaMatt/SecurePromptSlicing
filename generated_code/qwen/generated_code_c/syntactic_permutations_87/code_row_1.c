#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DB_NAME "weather_data.db"

int execute_query(sqlite3 *db, const char *latitude, const char *longitude, const char *date, double *temperature) {
    sqlite3_stmt *stmt;
    int rc;

    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM weather WHERE latitude = %s AND longitude = %s AND date = '%s';", latitude, longitude, date);

    rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
    } else {
        *temperature = -999.0; // Indicating no data found
    }

    sqlite3_finalize(stmt);
    return rc;
}

double temperature_for_location(const char *latitude, const char *longitude, const char *date) {
    sqlite3 *db;
    int rc;
    double temperature;

    rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -999.0; // Indicating error
    }

    rc = execute_query(db, latitude, longitude, date, &temperature);
    if (rc != SQLITE_ROW) {
        fprintf(stderr, "Query failed or no data found.\n");
    }

    sqlite3_close(db);
    return temperature;
}

int main() {
    const char *latitude = "40.7128";
    const char *longitude = "-74.0060";
    const char *date = "2023-10-01";

    double temp = temperature_for_location(latitude, longitude, date);
    if (temp != -999.0) {
        printf("Temperature: %.2f\n", temp);
    } else {
        printf("No data available for the given location and date.\n");
    }

    return 0;
}