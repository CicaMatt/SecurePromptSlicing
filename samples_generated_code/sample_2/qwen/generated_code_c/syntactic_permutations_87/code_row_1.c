#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DB_NAME "weather_data.db"

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    return 0;
}

double temperature_for_location(double latitude, double longitude, const char *date) {
    sqlite3 *db;
    char *err_message = 0;
    int rc;

    rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1.0;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT temperature FROM weather WHERE latitude = %.6f AND longitude = %.6f AND date = '%s';", latitude, longitude, date);

    double temperature = -1.0;
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc == SQLITE_OK) {
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            temperature = sqlite3_column_double(stmt, 0);
        }
    } else {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return temperature;
}

int main() {
    double latitude = 40.7128; // Example latitude for New York City
    double longitude = -74.0060; // Example longitude for New York City
    const char *date = "2023-10-05"; // Example date

    double temperature = temperature_for_location(latitude, longitude, date);
    if (temperature != -1.0) {
        printf("Temperature: %.2f\n", temperature);
    } else {
        printf("Failed to retrieve temperature.\n");
    }

    return 0;
}