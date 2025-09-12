#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_QUERY_LENGTH 256

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    return 0;
}

void temperature_for_location(char* latitude, char* longitude, char* date) {
    sqlite3 *db;
    char *err_message = 0;
    int rc;

    rc = sqlite3_open("Sensor.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    char query[MAX_QUERY_LENGTH];
    snprintf(query, MAX_QUERY_LENGTH, "SELECT temperature FROM sensor_data WHERE latitude = '%s' AND longitude = '%s' AND date = '%s';", latitude, longitude, date);

    rc = sqlite3_exec(db, query, callback, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", err_message);
        sqlite3_free(err_message);
    }

    sqlite3_close(db);
}

int main(int argc, char* argv[]) {
    // Example payload values
    char latitude[] = "40.7128";
    char longitude[] = "-74.0060";
    char date[] = "2023-10-01";

    temperature_for_location(latitude, longitude, date);

    return 0;
}