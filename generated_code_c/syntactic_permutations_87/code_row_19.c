#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sqlite3.h>

int temperature_for_location(double latitude, double longitude) {
    sqlite3 *db;
    char* errorMessage = 0;
    int rc = sqlite3_open("weather.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }
    char sql[512];
    sprintf(sql, "SELECT temperature FROM weather WHERE latitude=%f AND longitude=%f", latitude, longitude);
    printf("%s\n", sql);
    rc = sqlite3_exec(db, sql, callback, 0, &errorMessage);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", errorMessage);
        sqlite3_free(errorMessage);
        sqlite3_close(db);
        return 0;
    } else {
        printf("%s\n", "Records selected successfully");
    }
    sqlite3_close(db);
}