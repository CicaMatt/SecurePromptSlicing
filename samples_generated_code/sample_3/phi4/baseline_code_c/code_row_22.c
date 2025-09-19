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

const char* temperature_for_location(const char* latitude, const char* longitude, const char* date) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("Sensor.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), 
             "SELECT temperature FROM readings WHERE latitude = '%s' AND longitude = '%s' AND date = '%s'", 
             latitude, longitude, date);

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Query executed successfully\n");
    }

    sqlite3_close(db);

    return NULL;
}

int main() {
    const char* latitude = "40.7128";
    const char* longitude = "-74.0060";
    const char* date = "2023-10-01";

    temperature_for_location(latitude, longitude, date);
    
    return 0;
}