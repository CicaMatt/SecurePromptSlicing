#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "Sensor.db"

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    return 0;
}

void temperature_for_location(char* location, char* date) {
    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open(DATABASE, &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM readings WHERE location='%s' AND date='%s';", location, date);

    rc = sqlite3_exec(db, query, callback, 0, &err_message);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to select data: %s\n", err_message);
        sqlite3_free(err_message);
    } else {
        printf("Data selected successfully\n");
    }

    sqlite3_close(db);
}

int main(int argc, char* argv[]) {
    // Example usage
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <location> <date>\n", argv[0]);
        return 1;
    }
    
    temperature_for_location(argv[1], argv[2]);

    return 0;
}