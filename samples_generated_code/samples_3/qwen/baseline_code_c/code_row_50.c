#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    return 0;
}

void temperature_for_location(double latitude, double longitude, const char *date) {
    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open("Sensor.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), 
             "SELECT temperature FROM weather_data WHERE latitude = %.6f AND longitude = %.6f AND date = '%s';",
             latitude, longitude, date);

    rc = sqlite3_exec(db, sql, callback, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", err_message);
        sqlite3_free(err_message);
    }

    sqlite3_close(db);
}

int main() {
    double latitude = 40.7128;
    double longitude = -74.0060;
    const char *date = "2023-10-01";

    temperature_for_location(latitude, longitude, date);

    return 0;
}