#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sqlite3.h"

#define DATABASE "temperature_database.db"
#define SQL_QUERY "SELECT temperature FROM temperature_table WHERE latitude = ? and longitude = ? and date = ?"

int temperature_for_location(float latitude, float longitude, char* date){
    sqlite3 *db;
    int rc;
    sqlite3_stmt *res;
    const char *tail;
    char *errmsg = 0;

    if (sqlite3_open(DATABASE, &db) != SQLITE_OK) {
        printf("Failed to open database.");
        return -1;
    }

    rc = sqlite3_prepare_v2(db, SQL_QUERY, strlen(SQL_QUERY), &res, &tail);

    if (rc != SQLITE_OK) {
        errmsg = "Failed to prepare statement.";
        goto error;
    }

    rc = sqlite3_bind_double(res, 1, latitude);
    if (rc != SQLITE_OK){
        errmsg = "Failed to bind longitude.";
        goto error;
    }

    rc = sqlite3_bind_double(res, 2, longitude);
    if (rc != SQLITE_OK){
        errmsg = "Failed to bind latitude.";
        goto error;
    }

    rc = sqlite3_bind_text(res, 3, date, strlen(date), SQLITE_STATIC);
    if (rc != SQLITE_OK){
        errmsg = "Failed to bind date.";
        goto error;
    }

    int temperature;
    rc = sqlite3_step(res);
    if (rc == SQLITE_ROW) {
        temperature = sqlite3_column_int(res, 0);
    } else {
        errmsg = "No data available.";
        goto error;
    }

    rc = sqlite3_finalize(res);
    if (rc != SQLITE_OK) {
        errmsg = "Failed to finalize statement.";
        goto error;
    }

    sqlite3_close(db);
    return temperature;

error:
    fprintf(stderr, "%s\n", errmsg);
    sqlite3_finalize(res);
    sqlite3_close(db);
    return -1;
}