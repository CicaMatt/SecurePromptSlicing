#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DB_PATH "weather_data.db"

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for(int i=0; i<argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    return 0;
}

void temperature_for_location(double latitude, double longitude, const char* date) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open(DB_PATH, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    } else {
        fprintf(stdout, "Opened database successfully\n");
    }

    char query[256];
    snprintf(query, sizeof(query),
             "SELECT temperature FROM weather_data WHERE latitude = %.6f AND longitude = %.6f AND date = '%s';",
             latitude, longitude, date);

    rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Operation done successfully\n");
    }

    sqlite3_close(db);
}

int main() {
    // Example usage
    double latitude = 40.7128;
    double longitude = -74.0060;
    const char* date = "2023-10-05";

    temperature_for_location(latitude, longitude, date);

    return 0;
}