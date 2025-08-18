#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_QUERY_LENGTH 256

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    if (argc == 1 && argv[0]) {
        printf("%s\n", argv[0]);
    }
    return 0;
}

void temperature_for_location(const char* latitude, const char* longitude, const char* date) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("Sensor.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    char query[MAX_QUERY_LENGTH];
    snprintf(query, MAX_QUERY_LENGTH,
             "SELECT temperature FROM sensor_data WHERE latitude = '%s' AND longitude = '%s' AND date = '%s';",
             latitude, longitude, date);

    rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    sqlite3_close(db);
}

int main() {
    const char* latitude = "40.7128";
    const char* longitude = "-74.0060";
    const char* date = "2023-10-05";

    temperature_for_location(latitude, longitude, date);

    return 0;
}